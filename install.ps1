#!/usr/bin/env pwsh

# Twindows Installation Script
# Created by Berkay AY (shadesofdeath)
# https://github.com/shadesofdeath/Twindows

# Function definitions
function Test-Admin {
    $currentUser = New-Object Security.Principal.WindowsPrincipal([Security.Principal.WindowsIdentity]::GetCurrent())
    return $currentUser.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Get-LatestRelease {
    [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
    $releases = "https://api.github.com/repos/shadesofdeath/Twindows/releases/latest"
    $tag = (Invoke-WebRequest $releases -UseBasicParsing | ConvertFrom-Json).tag_name
    $download = "https://github.com/shadesofdeath/Twindows/releases/download/$tag/Twindows.zip"
    return $download
}

# Display banner
Write-Host "
---------------------------------------------
             TWINDOWS INSTALLER             
   Ultimate Windows 11 Optimization Suite   
---------------------------------------------
" -ForegroundColor Cyan

# Check if running as admin
if (-not (Test-Admin)) {
    Write-Host "Twindows requires administrator privileges." -ForegroundColor Yellow
    Write-Host "Requesting elevation..." -ForegroundColor Yellow
    
    # Relaunch as admin
    Start-Process PowerShell -ArgumentList "-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"" -Verb RunAs
    exit
}

# Ask where to install
Write-Host "Where would you like to install Twindows?" -ForegroundColor Green
Write-Host "1) Program Files (recommended)" -ForegroundColor White
Write-Host "2) Desktop" -ForegroundColor White
Write-Host "3) Custom location" -ForegroundColor White
$installChoice = Read-Host "Enter your choice (1-3)"

switch ($installChoice) {
    "1" { $installPath = "$env:ProgramFiles\Twindows" }
    "2" { $installPath = "$env:USERPROFILE\Desktop\Twindows" }
    "3" { 
        $customPath = Read-Host "Enter the full path where you want to install Twindows"
        $installPath = $customPath
    }
    default { $installPath = "$env:ProgramFiles\Twindows" }
}

# Create directory if it doesn't exist
if (-not (Test-Path -Path $installPath)) {
    New-Item -ItemType Directory -Path $installPath -Force | Out-Null
}

# Download the latest release
Write-Host "Downloading Twindows latest version..." -ForegroundColor Cyan
$downloadUrl = Get-LatestRelease
$zipPath = "$env:TEMP\Twindows.zip"

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

# Cleanup
Remove-Item $zipPath -Force

# Create desktop shortcut
$WshShell = New-Object -ComObject WScript.Shell
$Shortcut = $WshShell.CreateShortcut("$env:USERPROFILE\Desktop\Twindows.lnk")
$Shortcut.TargetPath = "$installPath\Twindows.exe"
$Shortcut.Save()

Write-Host "Installation completed successfully!" -ForegroundColor Green
Write-Host "Twindows has been installed to: $installPath" -ForegroundColor White
Write-Host "A shortcut has been created on your desktop." -ForegroundColor White

# Ask to run the application
$runNow = Read-Host "Would you like to run Twindows now? (Y/N)"
if ($runNow -eq "Y" -or $runNow -eq "y") {
    Write-Host "Launching Twindows..." -ForegroundColor Cyan
    Start-Process -FilePath "$installPath\Twindows.exe"
}

Write-Host "Thank you for installing Twindows!" -ForegroundColor Cyan
Write-Host "If you like Twindows, please consider giving us a star on GitHub:" -ForegroundColor White
Write-Host "https://github.com/shadesofdeath/Twindows" -ForegroundColor Cyan

# Countdown before closing
Write-Host "`nThis window will close in:" -ForegroundColor Yellow
5..1 | ForEach-Object {
    Write-Host "$_..." -ForegroundColor Yellow
    Start-Sleep -Seconds 1
} 