#include "file.h"

wchar_t* getCurrentDirectory()
{
	static wchar_t* buffer = new wchar_t[256];
	GetCurrentDirectory(256, buffer);
	return buffer;
}