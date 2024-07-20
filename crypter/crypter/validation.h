#pragma once
#include <windows.h>

// Validation details. Enable VALIDATION_DEBUG to see debug output, but it's not necessary to 
// test the encryption algorithm. If the algorithm is wrong, the validator will report it even
// if VALIDATION_DEBUG is false.
#define VALIDATION_DEBUG FALSE
#define VALIDATION_ROUNDS 25  // How many rounds of validation to do on the encryption algorithm
#define VALIDATION_DATA_MAXLEN 1024
#define VALIDATION_DATA_MINLEN 1
#define VALIDATION_KEY_MAXLEN 255
#define VALIDATION_KEY_MINLEN 1

// Validate encryption and decryption methods return the same data.
BOOL validateEncryptDecrypt(
	VOID(*encrypt)(const char* key, const SIZE_T keyLen, char* src, const SIZE_T srcLen),
	VOID(*decrypt)(const char* key, const SIZE_T keyLen, char* src, const SIZE_T srcLen)
);