#pragma once
#include <Windows.h>

// Dumps the hex-encoded shellcode
VOID shellcodeDump(const char* s, const SIZE_T sLen);

// Provides a hexdump of the given data
VOID hexdump(const char* s, const SIZE_T sLen);