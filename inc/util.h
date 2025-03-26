#pragma once

inline const HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE StdIn = GetStdHandle(STD_INPUT_HANDLE);
inline const HANDLE processHeap = GetProcessHeap();

void* operator new(size_t size);
void* ralloc(void* memory, size_t size);

void error(const wchar_t* message);
void error(const wchar_t* message, DWORD code);

wchar_t* lower(wchar_t* source);
wchar_t lower(wchar_t c);

inline void print(const wchar_t* message);

template <size_t N>
inline void print(const wchar_t(&message)[N]) { WriteConsole(StdOut, message, N - 1, NULL, NULL); }

bool relaxedEquals(const wchar_t* s1, const wchar_t* s2);

size_t iSize(int number);