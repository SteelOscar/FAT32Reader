#pragma once

#ifdef FAT32VOLUMEINFO_EXPORTS
#define FAT32VOLUMEINFO_API __declspec(dllexport)
#else
#define FAT32VOLUMEINFO_API __declspec(dllimport)
#endif

#pragma pack(1)
typedef struct
{
	BYTE emptyBytes[3];
	BYTE OEM_ASCII[8];
	WORD bytesPerSector;
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
} FAT32;
#pragma pack()

extern "C++" FAT32VOLUMEINFO_API void execute(std::string diskName);
extern "C++" FAT32VOLUMEINFO_API std::string getVolumeFileSystemName(std::string diskName);
extern "C++" FAT32VOLUMEINFO_API bool checkVolumeFS(std::string fsName);