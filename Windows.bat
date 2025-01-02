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
echo Submodules have been updated successfully!

cmake -G"Visual Studio 2022" -S .
pause