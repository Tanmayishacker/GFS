#pragma once

#include <BaseFiles/Compression.hpp>

void LSTreeNoNameOnly(String &filePath) 
{
	String fileContent = readNormalFile(filePath);
	String outputBuffer = decompressDataZlib(fileContent);
	String output = outputBuffer;
	std::cout << outputBuffer;
}

void LSTreeNameOnly(String &filePath) 
{
	String fileContent = readNormalFile(filePath);
	
	if (fileContent == "")
	{
		std::cout << "";
	}
	else
	{
		String outputBuffer = decompressDataZlib(fileContent);
		String output = outputBuffer;
		std::cout << outputBuffer;
	}
}