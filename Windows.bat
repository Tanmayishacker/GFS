@echo off
:: Check if Git is installed
git --version > nul 2>&1
if %errorlevel% neq 0 (
    echo Git is not installed. Please install Git and try again.
    exit /b
)

echo "Downloading all submodules..........."
:: Initialize and update all submodules recursively
git submodule update --init --recursive

:: Optionally, notify the user when done
echo "Submodules have been updated successfully!"

REM Check if winget is installed
echo.
echo Checking for winget installation...

winget --version >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
    echo winget is installed.
) ELSE (
    echo winget is NOT installed.
)

echo You may get a prompt
echo.
setlocal

REM Check if ShiningLight OpenSSL Dev is installed
echo Checking for ShiningLight OpenSSL Dev installation...

REG QUERY "HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall" /s /f "ShiningLight.OpenSSL.Dev" >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
    echo ShiningLight OpenSSL Dev is installed.
) ELSE (
    echo ShiningLight OpenSSL Dev is NOT installed.
    echo you may install OpenSSL from https://slproweb.com/products/Win32OpenSSL.html
)

cmake -G"Visual Studio 2022" -S .
pause