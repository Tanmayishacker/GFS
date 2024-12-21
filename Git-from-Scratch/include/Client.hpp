#pragma once
// All the required modules will be here such as filesystem,fstream and other required files.
#include <HashObject.hpp>
#include <CatCommands.hpp>
#include <LSTree.hpp>

void handleCatCommand(String &flag,String &commitSHA) 
{
	if (flag == "-p")
	{
		std::cout << "Your given flag is: " + flag << "\n \n";
		catFileParameter_P(commitSHA);
	}
	
	else
	{
		std::cout << "Not a valid parameter!!";
	}
}

void handleHashObject(String& flag, String& filepath) 
{
	fs::path fullPath = fs::current_path().string() + '/' + filepath;
	String fullFolderPath = fullPath.string();

	bool isFileThere = true;
	bool isGitInitialized = fs::exists(fs::current_path().string() + '/' + ".git");
	if (!fs::exists(fullFolderPath))
	{
		isFileThere = false;
	}
#pragma region Hash map variables

	String hash = "";
	String blob = "";

	if (isFileThere == true)
	{
		String fileContent = readNormalFile(fullFolderPath);
		int fileLength = static_cast<int>(fileContent.size());
		hash = hashBySHA1(fileContent);
	}
	else
	{
		std::cerr << "could not open: " << "\"" + fullFolderPath + "\"" << " for reading: No such file or directory.\n";
	}

#pragma endregion

	if (isFileThere == true && flag == "")
	{
		std::cout << hash << std::endl;
	}

	else if (isFileThere == true && flag == "-w")
	{
		if (isGitInitialized== true)
		{
			hashObject_W(blob,hash);
		}
		else 
		{
			std::cout << "You must initilise a local repository";
		}
	}
	else
	{
		std::cerr << "Not Even a Parameter";
	}
}

void handleLSTree(String& flag , String& sha) 
{
#pragma region SHA Variables
	String folder = sha.substr(0, 2);
	String file = sha.substr(2);

	fs::path folderPath = fs::current_path().string() + '/' + ".git" +'/' +"objects" +'/' + folder;
	String fullFolderPath = get_file_path(folderPath.string());

	fs::path filePath = folderPath.string() + '/' + file;
	String fullFilePath = get_file_path(filePath.string());

	bool checker = true;

	if (!fs::exists(fullFolderPath))
	{
		std::cerr << "Not a valid object name " + sha + "\n";
		checker = false;
	}

	if (!fs::exists(fullFilePath) && checker == true)
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