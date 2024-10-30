#pragma once

#include <BaseFiles/FileReader.hpp>
#include <BaseFiles/Compression.hpp>

void catFileParameter_P(String &commitSHA)
{
	String file = commitSHA.substr(2);
	String folder = commitSHA.substr(0, 2);

	fs::path path = fs::current_path();
	path.append(".git/objects/" + folder + "/" + file);

	String fullPath = path.string();

	if(!fs::exists(path))
		std::cout << "Not a valid object name" + commitSHA;
	else
	{
		String readContent = BinaryFileReader(fullPath);
		String tempStringData = decompressDataZlib(readContent);
		std::cout << tempStringData;
	}
}