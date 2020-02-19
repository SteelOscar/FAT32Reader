#include "pch.h"
#include <iostream>
#include <windows.h>
#include "FAT32VolumeInfo.h"
#include <string>

void execute(std::string diskName) {
	std::string fsName = getVolumeFileSystemName(diskName);
}

std::string getVolumeFileSystemName(std::string diskName) {
	char lpVolumeNameBuffer[MAX_PATH];
	DWORD lpVolumeSerialNumber;
	DWORD lpMaximumComponentLength;
	DWORD lpFileSystemFlags;
	char lpFileSystemNameBuffer[MAX_PATH];

	bool dataReceived = GetVolumeInformationA(
		(diskName + ":\\").c_str(),
		lpVolumeNameBuffer,
		sizeof(lpVolumeNameBuffer),
		&lpVolumeSerialNumber,
		&lpMaximumComponentLength,
		&lpFileSystemFlags,
		lpFileSystemNameBuffer,
		sizeof(lpFileSystemNameBuffer)
	);

	if (!dataReceived) return "null";

	std::cout << "Volume name: " << lpVolumeNameBuffer << std::endl;
	std::cout << "Volume file system: " << lpFileSystemNameBuffer << std::endl;

	return lpFileSystemNameBuffer;
}