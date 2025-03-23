#include "parser.h"

argsArray parseArguments(const wchar_t* input, int length)
{
	static int argsMax = 32;
	static wchar_t** argv = (wchar_t**)alloc(argsMax * sizeof(wchar_t*));
	int argc = 0;

	static wchar_t* const basin = (wchar_t*)alloc(8192 * sizeof(wchar_t));
	int basinIndex = 0;
	int lastFlushIndex = 0;

	bool inString = false;
	bool escaped = false;
	bool escapedHex = false;
	short hexValue = 0;

	for (int i = 0; i < length + 1; i++)
	{
		wchar_t c = input[i];

		if (escaped)
		{
			if (c == L'x') escapedHex = true;
			else if (c == L'n') basin[basinIndex++] = L'\n';
			else if (c == L't') basin[basinIndex++] = L'\t';
			else if (c == L'0') basin[basinIndex++] = L'\0';
			else basin[basinIndex++] = c;
			escaped = false;
			continue;
		}
		if (escapedHex)
		{
			if (c >= L'0' && c <= L'9') c -= L'0';
			else if (std::tolower(c) >= L'a' && std::tolower(c) <= L'f') c = std::tolower(c) - L'a' + 10;
			else
			{
				basin[basinIndex++] = (wchar_t)hexValue;
				hexValue = 0;
				escapedHex = false;
			}
			if (escapedHex) hexValue = hexValue * 16 + c;
		}
		if (!escapedHex) {
			if (c == L' ' || c == '\t' || c == L'\0')
			{
				if (basinIndex - lastFlushIndex != 0 || input[i - 1] == L'"')
				{
					basin[basinIndex++] = 0;
					argv[argc++] = &basin[lastFlushIndex];
					if (argc == argsMax) argv = (wchar_t**)HeapReAlloc(processHeap, NULL, argv, (argsMax *= 2) * sizeof(wchar_t*));
					lastFlushIndex = basinIndex;
				}
			}
			else if (c == L'"') inString = !inString;
			else if (c == L'\\' && inString) escaped = true;
			else basin[basinIndex++] = c;
		}
	}

	return { argc, argv };
}