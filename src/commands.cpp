#include "pch.h"
#include "commands.h"

void args(const argsArray& args)
{

	if (args.argc == 0)
	{
		print(L"No arguments given.\n\n");
		return;
	}

	size_t argcSize = iSize(args.argc - 1);
	for (int i = 0; i < args.argc; i++)
	{
		wchar_t* buffer = new wchar_t[argcSize + wcslen(args.argv[i]) + 5]; // 5: sizeof(L"[]: \n")
		wchar_t format[] = L"[%0ni]: %s\n";
		format[3] = L'0' + (wchar_t)argcSize; // modifies n to the maximum size
		wsprintf(buffer, format, i, args.argv[i]);
		print(buffer);
	}
	print(L"\n");
}

void cd(const argsArray& args)
{
	static wchar_t** directories = new wchar_t* [32] {getCurrentDirectory()};
	static int max = 32;
	static int directoriesIndex = 0;

	if (args.argc == 0) print(getCurrentDirectory());

	bool validInteger = true;
	bool negative = args.argv[0][0] == L'-';
	if (negative || args.argv[0][0] == '+') args.argv[0]++;
	int number = 0;
	for (int i = 0; args.argv[0][i] != '\0'; i++)
	{
		if (args.argv[0][i] <= '0' || args.argv[0][i] >= '9')
		{
			validInteger = false;
			break;
		}
		number = number * 10 + args.argv[0][i] - '0';
	}
	if (negative) number = -number;
	if (validInteger)
	{
		if (number == 0)
		{
			print(getCurrentDirectory());
			return;
		}
		int newIndex = directoriesIndex + number;
		if (newIndex < 0)
		{
			error(L"There is no further history");
			return;
		}
		else if (newIndex > max)
		{
			error(L"There is no further future.");
			return;
		}
		SetCurrentDirectory(directories[directoriesIndex += number]);
		return;
	}

	DWORD attributes = GetFileAttributes(args.argv[0]);
	if (attributes != INVALID_FILE_ATTRIBUTES && attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		wchar_t* buffer = new wchar_t[MAX_PATH];
		GetLongPathName(args.argv[0], buffer, MAX_PATH);
		if (buffer[1] == L':' && buffer[0] <= L'z' && buffer[0] >= L'a') buffer[0] -= L'a' - L'A';
		if (relaxedEquals(buffer, getCurrentDirectory())) return;
		SetCurrentDirectory(buffer);
		if (directoriesIndex == max - 1) ralloc(directories, (max *= 2) * sizeof(wchar_t*));
		directories[max = ++directoriesIndex] = buffer;
	}
	else error(L"Directory does not exist.");
}

void clear(const argsArray& args) { print(L"\x1b[2J\x1b[3J\x1B[H"); }

commandFunction locateFunction(const wchar_t* name)
{
	for (int i = 0; i < sizeof(commands) / sizeof(command); i++) if (relaxedEquals(commands[i].name, name)) return commands[i].function;
	return nullptr;
}