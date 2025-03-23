#pragma once
#include <string>
#include <Windows.h>

inline const HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE StdIn = GetStdHandle(STD_INPUT_HANDLE);
inline const HANDLE processHeap = GetProcessHeap();

inline void* alloc(DWORD size) { return HeapAlloc(processHeap, NULL, size); }

void error(const wchar_t* message);

wchar_t* lower(wchar_t* source);

inline void print(const wchar_t* message);

template <size_t N>
inline void print(const wchar_t(&message)[N]) { WriteConsole(StdOut, message, N - 1, NULL, NULL); }

bool relaxedEquals(const wchar_t* s1, const wchar_t* s2);

size_t iSize(int number);