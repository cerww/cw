#ifndef IOMANAGER_H
#define IOMANAGER_H
#pragma once
#include <vector>
#include <string>
#include <fstream>
struct IOmanager
{
	static bool readFileToBuffer(const std::string& filePath,std::vector<unsigned char>& buffer);
};

#endif // IOMANAGER_H
