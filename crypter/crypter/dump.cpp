#include <Windows.h>
#include <stdio.h>
#include "dump.h"

// Dumps the hex-encoded shellcode
VOID shellcodeDump(const char* s, const SIZE_T sLen)
{
	printf("{");
	for (SIZE_T i = 0; i < sLen; i++) {
		printf("0x%02x", ((unsigned int)s[i]) & 0xFF);
		if (i + 1 != sLen)
			printf(", ");
	}
	printf("}\n");
}

// Provides a hexdump of the given data
VOID hexdump(const char* s, const SIZE_T sLen)
{
	for (SIZE_T i = 0; i < sLen; i++) {
		printf("%02x", ((unsigned int)s[i]) & 0xFF);
		if (i + 1 != sLen)
			printf(" ");
	}
}
