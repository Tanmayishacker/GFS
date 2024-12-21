#pragma once
#include "commanInclude.hpp"

std::string BinaryFileReader(String &completeFilePath)
{
    std::ifstream file(completeFilePath, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Could not open file " << completeFilePath << std::endl;
        return "";
    }

    std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return data;
}

void writeToFile(const String& directory, const String& filename, const String& data)
{
    // Create the directory if it doesn't exist
    fs::create_directories(directory);

    // Define the full path for the file
    std::string fPath = directory + '/' + filename;
    String fullPath = get_file_path(fPath);
    // Open the file in write mode
    std::ofstream outfile(fullPath);

    if (!outfile) {
        return; // Exit if file creation failed
    }

    // Write the data to the file
    outfile << data;

    // Close the file
    outfile.close();
}

std::string readNormalFile(const String& filePath) {
    std::ifstream file(filePath); // Open the file
    if (!file.is_open()) { // Check if the file was opened successfully
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return ""; // Return an empty string if the file can't be opened
    }
    // Read the contents of the file into a string
    String content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close(); // Close the file
    return content; // Return the contents of the file
}