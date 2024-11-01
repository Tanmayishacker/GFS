#pragma once
// All the required modules will be here such as filesystem,fstream and other required files.
#include <HashObject.hpp>
#include <CatCommands.hpp>

void handleCatCommand(std::string &flag,std::string &commitSHA) 
{
	if (flag == "-p")
	{
		std::cout << "Your given flag is: " + flag << std::endl << std::endl;
		catFileParameter_P(commitSHA);
	}
	
	else
	{
		std::cout << "Not a valid parameter!!";
	}
}

void handleHashObject(String& flag, String& filepath) 
{
#pragma region Hash map variables

	String hash = "";
	String blob = "";

	bool freeCommand = true;

	fs::path fullPath = fs::current_path();
	fullPath.append(filepath);

	if (!fs::exists(fullPath))
	{
		freeCommand = false;
		std::cerr << "could not open: " << "\"" + filepath + "\"" << " for reading: No such file or directory" << std::endl; 
	}
	else
	{
		String fileContent = readNormalFile(fullPath.string());
		int fileLength = static_cast<int>(fileContent.size());

		String header = "blob" + std::to_string(fileLength) + "\0";
		blob = header + fileContent;

		hash = hashBySHA1(blob);
	}

#pragma endregion

	if (freeCommand == true && flag == "")
	{
		std::cout << hash << std::endl;
	}

	else if (flag == "-w")
	{
		hashObject_W(blob,hash);
	}

	else
		std::cout << "Not a valid parameter!" << std::endl;
}

void handleLsTree() 
{
	
}