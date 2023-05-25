#include <iostream>
#include <filesystem>
#include <string>
#include "Headers/FileOperations.h"

namespace fs = std::filesystem;

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

		//If file with same name exists in folder, rename file
		if (fs::exists(folderName + "/" + fileName)) {
			int fileNumber = 1;

			//check if file with number exists
			while (fs::exists(folderName + "/" + fileName.substr(0, fileName.find_last_of(".")) + '_' + std::to_string(fileNumber) + fileName.substr(fileName.find_last_of("."))))
				fileNumber++;

			//rename file with number before file extension
			fs::rename(fileName, folderName + "/" + fileName.substr(0, fileName.find_last_of(".")) + '_' + std::to_string(fileNumber) + fileName.substr(fileName.find_last_of(".")));
		}
		else fs::rename(fileName, folderName + "/" + fileName);
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
	catch (const std::exception& e) {
		std::cout << "Error :  " << e.what() << std::endl;
	}
}