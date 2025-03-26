#include "pch.h"
#include "file.h"

wchar_t* getCurrentDirectory()
{
	wchar_t* buffer = new wchar_t[MAX_PATH];
	if (!GetCurrentDirectory(MAX_PATH, buffer)) return nullptr;
	return buffer;
}