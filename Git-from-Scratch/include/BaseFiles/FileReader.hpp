#pragma once
#include <string>
#include <iostream>

std::string BinaryFileReader(std::string completeFilePath)
{
    std::ifstream file(completeFilePath, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Could not open file " << completeFilePath << std::endl;
        return "";
    }

    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return data;
}

void writeToFile(const std::string& directory, const std::string& filename, const std::string& data)
{
    // Create the directory if it doesn't exist
    std::filesystem::create_directories(directory);

    // Define the full path for the file
    std::string fullPath = directory + "/" + filename;

    // Open the file in write mode
    std::ofstream outfile;

    if (!outfile) {
        return; // Exit if file creation failed
    }

    // Write the data to the file
    outfile << data;

    // Close the file
    outfile.close();
}