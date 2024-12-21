#pragma once

#include <BaseFiles/FileReader.hpp>
#include <BaseFiles/Compression.hpp>

void catFileParameter_P(String &commitSHA)
{
	String file = commitSHA.substr(2);
	String folder = commitSHA.substr(0, 2);

	fs::path path = fs::current_path().string() + ".git" + '/' +"objects" +'/' + folder + '/' + file;

	String fullPath = get_file_path(path.string());

	if(!fs::exists(fullPath))
		std::cout << "Not a valid object name" + commitSHA;
	else
	{
		String readContent = BinaryFileReader(fullPath);
		String tempStringData = decompressDataZlib(readContent);
		std::cout << tempStringData;
	}
}