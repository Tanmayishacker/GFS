#pragma once

#include <BaseFiles/FileReader.hpp>
#include <BaseFiles/Compression.hpp>

void hashObject_W(String &blob,String &hash)
{
	String folder = hash.substr(0, 2);
	String fileName = hash.substr(2);

	fs::path completeFolderPath = fs::current_path().string() + ".git" + "\\" +"objects" + "\\" + folder;

	if (!fs::exists(completeFolderPath))
		fs::create_directory(completeFolderPath);

	String compressedData = compressDataZlib(blob);

	writeToFile(completeFolderPath.string(), fileName, compressedData);

	std::cout << hash << std::endl;

}