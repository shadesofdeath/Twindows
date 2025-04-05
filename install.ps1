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
$exePath = "$installPath\Twindows.exe"

# Create directory
New-Item -ItemType Directory -Path $installPath -Force | Out-Null

# Download the executable using GitHub API
Write-Host "Downloading Twindows latest version..." -ForegroundColor Cyan

# Define the GitHub API URL
$apiUrl = "https://api.github.com/repos/shadesofdeath/Twindows/releases/latest"

try {
    # Set TLS 1.2 for HTTPS connections
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    
    # Get latest release info with proper headers
    $releaseInfo = Invoke-RestMethod -Uri $apiUrl -Headers @{
        "Accept"     = "application/vnd.github.v3+json"
        "User-Agent" = "Twindows-PowerShell-Launcher"
    }
    
    # Get the tag name
    $tagName = $releaseInfo.tag_name
    Write-Host "Found latest version: $tagName" -ForegroundColor Green
    
    # Get the download URL for the executable
    $assets = $releaseInfo.assets
    if ($assets -and $assets.Count -gt 0) {
        # Look for Twindows.exe in assets
        $exeAsset = $assets | Where-Object { $_.name -eq "Twindows.exe" }
        if ($exeAsset) {
            $downloadUrl = $exeAsset.browser_download_url
        } else {
            # If not found, try the first asset
            $downloadUrl = $assets[0].browser_download_url
        }
    } else {
        # Fallback to a constructed URL
        $downloadUrl = "https://github.com/shadesofdeath/Twindows/releases/download/$tagName/Twindows.exe"
    }
    
    Write-Host "Downloading from: $downloadUrl" -ForegroundColor DarkGray
    
    # Download the file with proper headers
    Invoke-WebRequest -Uri $downloadUrl -OutFile $exePath -Headers @{
        "User-Agent" = "Twindows-PowerShell-Launcher"
    } -UseBasicParsing
    
    # Verify the download
    if (-not (Test-Path -Path $exePath) -or (Get-Item -Path $exePath).Length -eq 0) {
        throw "Downloaded file is empty or doesn't exist"
    }
    
    Write-Host "Download successful!" -ForegroundColor Green
}
catch {
    Write-Host "GitHub API or download failed: $_" -ForegroundColor Red
    
    # Try fallback download URLs
    Write-Host "Trying fallback download methods..." -ForegroundColor Yellow
    
    $fallbackUrls = @(
        "https://github.com/shadesofdeath/Twindows/releases/latest/download/Twindows.exe",
        "https://github.com/shadesofdeath/Twindows/releases/download/v1.0.0.0/Twindows.exe"
    )
    
    $downloadSuccess = $false
    
    foreach ($url in $fallbackUrls) {
        try {
            Write-Host "Trying: $url" -ForegroundColor DarkGray
            Invoke-WebRequest -Uri $url -OutFile $exePath -UseBasicParsing -TimeoutSec 30
            
            if ((Test-Path -Path $exePath) -and (Get-Item -Path $exePath).Length -gt 0) {
                $downloadSuccess = $true
                Write-Host "Fallback download successful!" -ForegroundColor Green
                break
            }
        } catch {
            Write-Host "Fallback attempt failed: $_" -ForegroundColor Red
            continue
        }
    }
    
    if (-not $downloadSuccess) {
        Write-Host "All download attempts failed." -ForegroundColor Red
        Write-Host "Please download Twindows manually from: https://github.com/shadesofdeath/Twindows/releases" -ForegroundColor Yellow
        pause
        # Clean up temp directory
        Remove-Item -Path $installPath -Recurse -Force -ErrorAction SilentlyContinue
        exit
    }
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