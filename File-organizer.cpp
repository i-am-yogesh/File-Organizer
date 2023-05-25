// File-organizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;

std::map<std::string, std::string> fileTypes = {
	{"txt", "Text"},
	{"doc", "Word"},
	{"docx", "Word"},
	{"pdf", "PDF"},
	{"jpg", "Image"},
	{"png", "Image"},
	{"gif", "Image"},
	{"mp3", "Music"},
	{"wav", "Music"},
	{"mp4", "Video"},
	{"avi", "Video"},
	{"zip", "Compressed"},
	{"rar", "Compressed"}
};

std::string currentFileType;
std::string currentLocation;

//Make directory at location
bool createFolder(std::string folderName)
{
	//std::cout << folderName << std::endl;
	try {
		fs::create_directory(folderName);
		return true;
	}
	catch (fs::filesystem_error& e) {
		std::cout << "Failed to create directory " << e.what() << std::endl;
		return false;
	}
	
}

//Move file to folder
bool moveFile(std::string fileName, std::string folderName)
{
	try {
		fs::rename(fileName,  folderName + "/" + fileName);
		return true;
	}
	catch (fs::filesystem_error& e) {
		std::cout << "Failed to move file " << e.what() << std::endl;
		return false;
	}
}

//get location of current floder
std::string getCurrentLocation()
{
	return fs::current_path().string();
}


//Determines file type by file extension and excludes folders
std::string getFileType(std::string fileName)
{
	std::string fileType = fileName.substr(fileName.find_last_of(".") + 1);
	return fileType;
}

//scan directory for files
void scanDirectory(std::string directoryName)
{
	try {
		for (const auto& entry : fs::directory_iterator(directoryName)) {
			currentFileType = getFileType(entry.path().filename().string());
			std::cout << currentFileType << std::endl;
			if (fileTypes.find(currentFileType) != fileTypes.end()) {
				//currentFileType = "";
				createFolder(fileTypes[currentFileType]);
				moveFile(entry.path().filename().string(), fileTypes[currentFileType]);
			}
			
		}
	}
	catch(const std::exception& e) {
		std::cout << "Error :  " << e.what() << std::endl;
	}
}


int main()
{
	currentLocation = getCurrentLocation();
	scanDirectory(currentLocation);

	return 0;
}
