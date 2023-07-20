#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 124
void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

int readInt(const char* section, const char* keyword, int defaultValue, const char* filePath) {

	return GetPrivateProfileInt(section, keyword, -1, filePath);

}

bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {

	return GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath);
}