#include "commands.h"

void args(const argsArray& args)
{
	for (int i = 0; i < args.argc; i++)
	{
		std::wstring index = std::to_wstring(i);
		index += std::wstring(iSize(args.argc - 1) - index.length(), '0');
		print((L"[" + index + L"]: " + args.argv[i] + L"\n").c_str());
	}
	print(L"\n");
}

void cd(const argsArray& args)
{
	if (args.argc == 0)
	{
		print(getCurrentDirectory());
		print(L"\n\n");
	}
	else
	{
		DWORD attributes = GetFileAttributes(args.argv[0]);
		if (attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY) SetCurrentDirectory(args.argv[0]);
		else error(L"Directory does not exist.");
	}
}

void clear(const argsArray& args) { print(L"\x1b[2J\x1b[3J\x1B[H"); }

commandFunction locateFunction(const wchar_t* name)
{
	for (int i = 0; i < sizeof(commands) / sizeof(command); i++)
		if (relaxedEquals(commands[i].name, name))
			return commands[i].function;
	return nullptr;
}