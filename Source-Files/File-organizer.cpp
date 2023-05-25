#include <iostream>
#include "Headers/FileOperations.h"
#include "Headers/FileTypes.h"

int main() {
	std::string currentLocation = getCurrentLocation();
	scanDirectory(currentLocation);

	return 0;
}

