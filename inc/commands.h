#pragma once
#include "file.h"
#include "util.h"

struct argsArray {
	int argc;
	wchar_t** argv;
};
typedef void(*commandFunction)(const argsArray&);

void args(const argsArray& args);
void cd(const argsArray& args);
void clear(const argsArray& args);

struct command {
	const wchar_t* name;
	commandFunction function;
};

inline command commands[] = { { L"args", args }, { L"cd", cd }, { L"clear", clear } };

commandFunction locateFunction(const wchar_t* name);