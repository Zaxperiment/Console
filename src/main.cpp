#include "tokeniser.h"

static void run()
{
	wchar_t* input = (wchar_t*)alloc(8192 * sizeof(wchar_t));
	DWORD length = 0;
	while (true)
	{
		const wchar_t* path = getCurrentDirectory();
		print(path);
		print(L"> ");
		ReadConsole(StdIn, input, 8192, &length, NULL);
		input[length -= 2] = 0;

		argsArray args = tokenise(input, length);
		if (args.argc == 0) continue;

		commandFunction f = locateFunction(args.argv[0]);
		if (f == nullptr)
		{
			std::wstring x = args.argv[0];
			x = L"'" + x + L"' is not callable.";
			error(x.c_str());
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