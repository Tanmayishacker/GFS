#pragma once

#include <BaseFiles/FileReader.hpp>
#include <BaseFiles/Compression.hpp>

namespace fs = std::filesystem;

void catFileParameter_P(std::string &commitSHA)
{
	const std::string file = commitSHA.substr(2);
	const std::string folder = commitSHA.substr(0, 2);

	fs::path path = fs::current_path();
	path.append(".git/objects/" + folder + "/" + file);

	std::string fullPath = path.string();

	if(!fs::exists(path))
		std::cout << "Not a valid object name" + commitSHA;
	else
	{
		std::string readContent = BinaryFileReader(fullPath);

		std::cout << decompressDataBoost(readContent);
	}
}
