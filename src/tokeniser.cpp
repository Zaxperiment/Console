#include "pch.h"
#include "tokeniser.h"

argsArray tokenise(const wchar_t* input, int length)
{
	static int argsMax = 32;
	static wchar_t** argv = new wchar_t*[argsMax];
	int argc = 0;

	static wchar_t* const basin = new wchar_t[8192];
	int basinIndex = 0;
	int lastFlushIndex = basinIndex;

	bool inString = false;
	bool escaped = false;
	bool escapedHex = false;
	short hexValue = 0;

	for (int i = 0; i <= length; i++)
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
			else if (lower(c) >= L'a' && lower(c) <= L'f') c = lower(c) - L'a' + 10;
			else
			{
				basin[basinIndex++] = hexValue;
				hexValue = 0;
				escapedHex = false;
			}
			if (escapedHex)
			{
				hexValue = hexValue * 16 + c;
				continue;
			}
		}
		if ((c == L' ' || c == L'\t') && !inString || c == L'\0')
		{
			if (basinIndex - lastFlushIndex != 0 || input[i - 1] == L'"')
			{
				basin[basinIndex++] = 0;
				argv[argc++] = &basin[lastFlushIndex];
				if (argc == argsMax)
				{
					wchar_t** p = (wchar_t**)ralloc(argv, (argsMax *= 2) * sizeof(wchar_t*));
					if (p == nullptr)
					{
						error(L"Could not re-allocate input buffer: too many arguments.");
						return { 0, nullptr };
					}
					argv = p;
				}
				lastFlushIndex = basinIndex;
			}
		}
		else if (c == L'"') inString = !inString;
		else if (c == L'\\' && inString) escaped = true;
		else basin[basinIndex++] = c;
	}

	if (inString)
	{
		error(L"Unmatched quotation mark.");
		return { 0, nullptr };
	}

	return { argc, argv };
}