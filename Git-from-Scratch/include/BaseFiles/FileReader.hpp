#pragma once
#include <commanInclude.hpp>

std::string BinaryFileReader(String completeFilePath)
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
    fs::create_directory(directory);

    // Define the full path for the file
    std::string fullPath = directory + "/" + filename;

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

std::string readNormalFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}