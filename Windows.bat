@echo off
:: Check if Git is installed
git --version > nul 2>&1
if %errorlevel% neq 0 (
    echo Git is not installed. Please install Git and try again.
    exit /b
)
echo.
echo "Downloading all submodules..........."
:: Initialize and update all submodules recursively
git submodule update --init --recursive

:: Optionally, notify the user when done
echo "Submodules have been updated successfully!"

REM Check if winget is installed
echo.
echo Checking for winget installation...

set IsWingetInstalled=false
winget --version >nul 2>&1

if %ERRORLEVEL% EQU 0 (
    echo Winget is installed.
    echo.
    set IsWingetInstalled=true
) else (
    echo winget is NOT installed.
    echo.
)

REM Check if ShiningLight OpenSSL Dev is installed
    echo Checking for ShiningLight OpenSSL Dev installation...

    :: Check if OpenSSL is installed by checking if openssl command is available
    openssl version >nul 2>&1

    if %ERRORLEVEL% EQU 0 (
        echo ShiningLight OpenSSL Dev is installed.
    ) else (

        echo ShiningLight OpenSSL Dev is NOT installed.
        echo.

        if %IsWingetInstalled%=="false" (
            echo ShiningLight OpenSSL Dev is NOT installed.
            echo you may install OpenSSL from https://slproweb.com/products/Win32OpenSSL.html
            exit /b
        ) 
        echo "You may get a prompt"
        echo.
        winget install -e --id ShiningLight.OpenSSL
        pause
    )

    echo "Select the build type from below:"
    echo "1) Release 2) Debug"

    set /p buildType="Build type:   "

    if %buildType%=="1"(
        cmake -DCMAKE_BUILD_TYPE=Release -S . -B ./build
    )
    else
    (
        cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./build
    )

exit /b