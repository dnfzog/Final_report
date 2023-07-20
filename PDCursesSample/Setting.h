#pragma once

int readInt(const char* section, const char* keyword, int defaultValue, const char* filePath);
void getGurrentDirectory(char* currentDirectory);
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);