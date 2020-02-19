#pragma once

#ifdef FAT32VOLUMEINFO_EXPORTS
#define FAT32VOLUMEINFO_API __declspec(dllexport)
#else
#define FAT32VOLUMEINFO_API __declspec(dllimport)
#endif

#include <windows.h>

#pragma pack(1)
typedef struct {
	BYTE emptyBytes[3];
	BYTE OEM_ASCII[8];
	WORD sectorSize;
	BYTE clusterFactor;
	WORD reservedAreaSize;
	BYTE copyFATCnt;
	WORD maxCntRecordsFAT1216;
	WORD sectorsCnt16;
	BYTE mediaType;
	WORD sizeFAT1216;
	WORD sectorsPerTrack;
	WORD headsCnt;
	DWORD sectorsBeforeStartSection;
	DWORD sectorsCnt32;
	DWORD sizeFAT32;
} FAT32;
#pragma pack()

extern "C++" FAT32VOLUMEINFO_API void execute(std::string diskName);
extern "C++" FAT32VOLUMEINFO_API std::string getVolumeFileSystemName(std::string diskName);
extern "C++" FAT32VOLUMEINFO_API bool checkVolumeFS(std::string fsName);
extern "C++" FAT32VOLUMEINFO_API bool getMBRData(std::string diskName, FAT32* volume);
extern "C++" FAT32VOLUMEINFO_API void showFAT32MBR(FAT32 volume);
extern "C++" FAT32VOLUMEINFO_API int calculateClusterSize(FAT32 volume);
extern "C++" FAT32VOLUMEINFO_API int calculateClusterCnt(FAT32 volume);
extern "C++" FAT32VOLUMEINFO_API int calculateFirstSectorFAT(FAT32 volume);
extern "C++" FAT32VOLUMEINFO_API int calculateFirstSectorRootDir(FAT32 volume);