#include "pch.h"
#include "util.h"

void* operator new(size_t size)
{
	void* p = HeapAlloc(processHeap, NULL, size);
	if (p == nullptr) error(L"Could not assign memory.", GetLastError());
	return p;
}

void* ralloc(void* memory, size_t size)
{
	void* p = HeapReAlloc(processHeap, NULL, memory, size);
	if (p == nullptr) error(L"Could not assign memory.", GetLastError());
	return p;
}

void error(const wchar_t* message)
{
	print(L"\x1B[31m");
	print(message);
	print(L"\x1B[0m\n\n");
}

void error(const wchar_t* message, DWORD code)
{
	print(L"\x1B[31m");
	print(message);
	print(L"\x1B[0m\n");
	exit(code);
	print(L"\n\n");
}

wchar_t* lower(wchar_t* source)
{
	for (int i = 0; source[i] != '\0'; i++) if (source[i] >= 'A' && source[i] <= 'Z') source[i] += 'a' - 'A';

	return source;
}

wchar_t lower(wchar_t c)
{
	if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
	return c;
}

inline void print(const wchar_t* message)
{
	if (!WriteConsole(StdOut, message, (DWORD)wcslen(message), NULL, NULL)) error(L"Failed to output characters.", GetLastError());
}

bool relaxedEquals(const wchar_t* s1, const wchar_t* s2)
{
	int index = 0;
	while (true)
	{
		if (lower(s1[index]) != lower(s2[index])) return false;
		else if (s1[index] == '\0') break;
		index++;
	}
	return true;
}

size_t iSize(int number)
{
	size_t size = 1;
	while ((number /= 10) > 0) size++;
	return size;
}