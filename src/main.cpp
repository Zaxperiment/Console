#include "pch.h"
#include "tokeniser.h"

static void run()
{
	wchar_t* input = new wchar_t[8194];
	DWORD length = 0;
	while (true)
	{
		const wchar_t* path = getCurrentDirectory();
		if (path != nullptr) print(path);
		print(L"> ");
		if (!ReadConsole(StdIn, input, 8194, &length, NULL)) error(L"Failed to read user input.", GetLastError());
		input[length -= 2] = 0;

		argsArray args = tokenise(input, length);
		if (args.argc == 0) continue;

		commandFunction f = locateFunction(args.argv[0]);
		if (f == nullptr)
		{
			wchar_t* buffer = new wchar_t[wcslen(args.argv[0]) + 20]; // 20: sizeof(L"'' is not callable.")
			wsprintf(buffer, L"'%s' is not callable.", args.argv[0]);
			error(buffer);
			continue;
		}
		f({ args.argc - 1, &args.argv[1] });
	}
}

int main(int argc, char* argv[])
{
	print(L"Console [1.0]\n\n");

	run();

	return 0;
}