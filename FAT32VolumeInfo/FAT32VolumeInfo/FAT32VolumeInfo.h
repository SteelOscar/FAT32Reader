#pragma once

#ifdef FAT32VOLUMEINFO_EXPORTS
#define FAT32VOLUMEINFO_API __declspec(dllexport)
#else
#define FAT32VOLUMEINFO_API __declspec(dllimport)
#endif

extern "C++" FAT32VOLUMEINFO_API void execute(std::string diskName);
extern "C++" FAT32VOLUMEINFO_API std::string getVolumeFileSystemName(std::string diskName);