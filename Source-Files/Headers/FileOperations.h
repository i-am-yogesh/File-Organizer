
// FileOperations.h
// Header file for FileOperations.cpp
#pragma once

#include <map>

bool createFolder(std::string folderName);
bool moveFile(std::string fileName, std::string folderName);
std::string getCurrentLocation();
std::string getFileType(std::string fileName);
void scanDirectory(std::string directoryName);

extern std::map<std::string, std::string> fileTypes;


