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
    std::ifstream file(filePath, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::ostringstream content;
    content << file.rdbuf(); // Read the entire buffer into the stream

    if (file.fail()) {
        throw std::runtime_error("Error occurred while reading file: " + filePath);
    }
    return content.str();
}