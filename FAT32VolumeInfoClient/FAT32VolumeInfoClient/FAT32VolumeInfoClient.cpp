#include <iostream>
#include "FAT32VolumeInfo.h"

using namespace std;

int main()
{
	string diskName;

	cout << "This application should be started as run administrator!" << endl;

	cout << "Please enter a volume letter: ";
	diskName = cin.get();

	string fsName = getVolumeFileSystemName(diskName);

	cout << "Press Enter to exit";
	cin.get();
	cin.get();
	exit(0);
}