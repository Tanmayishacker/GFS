#!/bin/bash

# Check if Git is installed
if ! git --version > /dev/null 2>&1; then
  echo "Git is not installed. Please install Git and try again."
  exit 1
fi

echo "Downloading all submodules..........."
# Initialize and update all submodules recursively
git submodule update --init --recursive

# Optionally, notify the user when done
echo "Submodules have been updated successfully!"

cmake -S .