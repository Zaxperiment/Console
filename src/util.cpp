#include "util.h"

void error(const wchar_t* message)
{
	print(L"\x1B[31m");
	print(message);
	print(L"\x1B[0m\n\n");
}

wchar_t* lower(wchar_t* source)
{
	for (int i = 0; source[i] != '\0'; i++) if (source[i] >= 'A' && source[i] <= 'Z') source[i] += 'a' - 'A';

	return source;
}

inline void print(const wchar_t* message)
{
	WriteConsole(StdOut, message, (DWORD)wcslen(message), NULL, NULL);
}

bool relaxedEquals(const wchar_t* s1, const wchar_t* s2)
{
	int index = 0;
	while (true)
	{
		if (s1[index] != s2[index]) return false;
		else if (s1[index] == s2[index] && s1[index] == '\0') break;
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