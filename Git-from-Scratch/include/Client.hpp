#pragma once
// All the required modules will be here such as filesystem,fstream and other required files.
#include <HashObject.hpp>
#include <CatCommands.hpp>
#include <LSTree.hpp>

void handleCatCommand(String &flag,String &commitSHA) 
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
		std::cerr << "could not open: " << "\"" + filepath + "\"" << " for reading: No such file or directory.\n"; 
	}
	else
	{
		String fileContent = readNormalFile(fullPath.string());
		int fileLength = static_cast<int>(fileContent.size());

		//String header = "blob" + std::to_string(fileLength) + "\0";
		//blob = header + fileContent;

		hash = hashBySHA1(fileContent);
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

void handleLSTree(String& flag , String& sha) 
{
#pragma region SHA Variables
	String folder = sha.substr(0, 2);
	String file = sha.substr(2);

	fs::path folderPath = fs::current_path().string() + "/.git/objects/" + folder;
	fs::path filePath = folderPath.string() + "/" + file;
	
	bool checker = true;

	if (!fs::exists(folderPath))
	{
		std::cerr << "Not a valid object name " + sha + "\n";
		checker = false;
	}

	if (!fs::exists(filePath) && checker == true)
	{
		std::cerr << "Not a valid object name " + sha ;
		checker = false;
	}
#pragma endregion
	
	String tempDataStorage = filePath.string();
	if (flag == "--name-only" && checker == true)
	{
		LSTreeNameOnly(tempDataStorage);
	}

	else if (flag.empty() && checker == true)
	{
		LSTreeNoNameOnly(tempDataStorage);
	}
}