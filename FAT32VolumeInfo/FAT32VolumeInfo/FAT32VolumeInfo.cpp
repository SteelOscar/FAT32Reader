#include "pch.h"
#include <iostream>
#include <windows.h>
#include "FAT32VolumeInfo.h"
#include <string>

void execute(std::string diskName) {
	std::string fsName = getVolumeFileSystemName(diskName);
	if (checkVolumeFS(fsName) and fsName != "null") {
		FAT32 volume;
		if (getMBRData(diskName, &volume)) {
			showFAT32MBR(volume);
		}
	} else {
		std::cout << "Invalid file system!" << std::endl;
		return;
	}
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

bool checkVolumeFS(std::string fsName) {
	if (fsName.find("FAT32") == -1) return false;
	return true;
}

bool getMBRData(std::string diskName, FAT32* volume) {
	BYTE lpBuffer[512];
	memset(lpBuffer, 0, 512);
	DWORD nNumberOfBytesToRead(0);

	std::string diskNameFormat = "\\\\.\\" + diskName + ":";

	HANDLE hFile = CreateFileA(
		diskNameFormat.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE |
		FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

	if (hFile == INVALID_HANDLE_VALUE) return false;

	ReadFile(hFile, lpBuffer, 512, &nNumberOfBytesToRead, NULL);

	CloseHandle(hFile);

	*volume = *reinterpret_cast<FAT32*>(lpBuffer);
	return true;
}

//change master develop
//new change in develop

void showFAT32MBR(FAT32 volume) {
	printf("OEM in ASCII: %s\n", volume.OEM_ASCII);
	printf("The number of bytes in the sector: %d\n", volume.sectorSize);
	printf("Cluster factor: %d\n", volume.clusterFactor);
	printf("Cluster size: %d bytes\n", calculateClusterSize(volume));
	printf("The number of clusters in FS : %d\n", calculateClusterCnt(volume));
	printf("First sector FAT: %d\n", calculateFirstSectorFAT(volume));
	printf("First sector root directory: %d\n", calculateFirstSectorRootDir(volume));
	printf("Reserved area size: %d sectors\n", volume.reservedAreaSize);
	printf("Number of copies FAT: %d\n", volume.copyFATCnt);
	printf("Media type (0xF8 - stationary, 0xF0 - removable) 0x%X\n", volume.mediaType);
	printf("The number of sectors in the track: %d\n", volume.sectorsPerTrack);
	printf("The number of heads: %d\n", volume.headsCnt);
	printf("The number of sectors before the start of the section: %d\n", volume.sectorsBeforeStartSection);
	printf("The number of sectors in the file system: %d\n", volume.sectorsCnt32);
}

int calculateClusterSize(FAT32 volume) {
	return volume.sectorSize * volume.clusterFactor;
}

int calculateClusterCnt(FAT32 volume) {
	return volume.sectorsCnt32 / volume.clusterFactor;
}

int calculateFirstSectorFAT(FAT32 volume) {
	return volume.reservedAreaSize + 1;
}

int calculateFirstSectorRootDir(FAT32 volume) {
	return volume.sizeFAT32 * volume.copyFATCnt + volume.reservedAreaSize;
}