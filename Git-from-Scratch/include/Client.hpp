#pragma once
// All the required modules will be here such as filesystem,fstream and other required files.
#include <commanInclude.hpp>
#include <CatCommands.hpp>

namespace fs = std::filesystem;

void handleCatCommand(std::string &flag,std::string &commitSHA) 
{
	if (flag == "-p")
	{
		catFileParameter_P(commitSHA);
	}
}