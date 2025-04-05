#!/usr/bin/env pwsh

# Twindows Installation Script
# Created by Berkay AY (shadesofdeath)
# https://github.com/shadesofdeath/Twindows

# Display banner
Write-Host "
---------------------------------------------
             TWINDOWS LAUNCHER             
   Ultimate Windows 11 Optimization Suite   
---------------------------------------------
" -ForegroundColor Cyan

# Function definitions
function Test-Admin {
    $currentUser = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
    return $currentUser.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Get-LatestRelease {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    $releases = "https://api.github.com/repos/shadesofdeath/Twindows/releases/latest"
    try {
        $tag = (Invoke-WebRequest $releases -UseBasicParsing | ConvertFrom-Json).tag_name
        $download = "https://github.com/shadesofdeath/Twindows/releases/download/$tag/Twindows.zip"
        return $download
    }
    catch {
        # Fallback to direct download if API fails
        return "https://github.com/shadesofdeath/Twindows/releases/latest/download/Twindows.zip"
    }
}

# Check if running as admin and elevate if needed
if (-not (Test-Admin)) {
    Write-Host "Twindows requires administrator privileges." -ForegroundColor Yellow
    Write-Host "Requesting elevation..." -ForegroundColor Yellow
    
    # Save script to temp file to execute as admin
    $tempScript = [System.IO.Path]::GetTempFileName() + ".ps1"
    $scriptContent = @'
    # Twindows temporary launcher
    Write-Host "Running with administrator privileges..." -ForegroundColor Green
    iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/shadesofdeath/Twindows/main/install.ps1'))
'@
    Set-Content -Path $tempScript -Value $scriptContent
    
    # Relaunch as admin
    Start-Process PowerShell.exe -ArgumentList "-NoProfile -ExecutionPolicy Bypass -File `"$tempScript`"" -Verb RunAs
    exit
}

# Create a random temporary directory for maximum portability
$randomId = [System.Guid]::NewGuid().ToString().Substring(0, 8)
$installPath = "$env:TEMP\Twindows_$randomId"

# Create directory
New-Item -ItemType Directory -Path $installPath -Force | Out-Null

# Download the latest release
Write-Host "Downloading Twindows latest version..." -ForegroundColor Cyan
$downloadUrl = Get-LatestRelease
$zipPath = "$installPath\Twindows.zip"

try {
    Invoke-WebRequest -Uri $downloadUrl -OutFile $zipPath -UseBasicParsing
}
catch {
    Write-Host "Failed to download Twindows. Please check your internet connection and try again." -ForegroundColor Red
    Write-Host "Error: $_" -ForegroundColor Red
    pause
    exit
}

# Extract the ZIP file
Write-Host "Extracting files..." -ForegroundColor Cyan
Expand-Archive -Path $zipPath -DestinationPath $installPath -Force

# Cleanup zip file
Remove-Item $zipPath -Force

# Find the executable
$exePath = Get-ChildItem -Path $installPath -Filter "Twindows.exe" -Recurse | Select-Object -First 1 -ExpandProperty FullName

if (-not $exePath) {
    Write-Host "Could not find Twindows.exe in the extracted files." -ForegroundColor Red
    Write-Host "Please report this issue on GitHub: https://github.com/shadesofdeath/Twindows/issues" -ForegroundColor Yellow
    pause
    exit
}

# Run the application
Write-Host "Launching Twindows..." -ForegroundColor Cyan
try {
    # Start process and get the process ID
    $process = Start-Process -FilePath $exePath -PassThru
    
    # Show running message
    Write-Host "Twindows is now running. Enjoy optimizing your Windows system!" -ForegroundColor Green
    
    # Set up automatic cleanup when the process exits
    $cleanupScript = {
        param($tempDir, $pid)
        # Wait for the process to exit
        try {
            Wait-Process -Id $pid -ErrorAction SilentlyContinue
        } catch {
            # Process may have already exited
        }
        # Allow some time for file handles to be released
        Start-Sleep -Seconds 2
        # Clean up the temp directory
        if (Test-Path $tempDir) {
            Remove-Item -Path $tempDir -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
    
    # Start a background job to clean up when the application closes
    Start-Job -ScriptBlock $cleanupScript -ArgumentList $installPath, $process.Id | Out-Null
}
catch {
    Write-Host "Error launching Twindows: $_" -ForegroundColor Red
    pause
    # Clean up if application failed to start
    Remove-Item -Path $installPath -Recurse -Force -ErrorAction SilentlyContinue
    exit
}

Write-Host "The launcher will close automatically in 3 seconds..." -ForegroundColor Yellow
Start-Sleep -Seconds 3 