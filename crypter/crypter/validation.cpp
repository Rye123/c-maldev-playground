#include <stdio.h>
#include <stdlib.h>
#include "dump.h"
#include "validation.h"

BOOL validateEncryptDecrypt(
	VOID(*encrypt)(const char* key, const SIZE_T keyLen, char* src, const SIZE_T srcLen),
	VOID(*decrypt)(const char* key, const SIZE_T keyLen, char* src, const SIZE_T srcLen)
) {
	SIZE_T dataLen = 0;
	SIZE_T keyLen = 0;
	char* data;
	char* key;

	for (SIZE_T i = 0; i < VALIDATION_ROUNDS; i++) {
		// Initialisation
		dataLen = rand() % (VALIDATION_DATA_MAXLEN + 1 - VALIDATION_DATA_MINLEN) + VALIDATION_DATA_MINLEN;
		keyLen = rand() % (VALIDATION_KEY_MAXLEN + 1 - VALIDATION_KEY_MINLEN) + VALIDATION_KEY_MINLEN;
		data = (char*)malloc(dataLen * sizeof(char));
		key = (char*)malloc(keyLen * sizeof(char));
		if (VALIDATION_DEBUG)
			printf("[V] Round %lld: Data length %lld, key length %lld\n", i, dataLen, keyLen);

		// Populate data and key with random data
		for (SIZE_T j = 0; j < dataLen; j++)
			data[j] = rand() % 256;
		for (SIZE_T j = 0; j < keyLen; j++)
			key[j] = rand() % 256;
		if (VALIDATION_DEBUG) {
			printf("[V] Round %lld:\n", i);
			printf("\tPlaintext: "); hexdump(data, dataLen); printf("\n");
			printf("\tKey: "); hexdump(key, keyLen); printf("\n");
		}

		// Start tests
		CHAR* buf = (CHAR*)malloc(dataLen * sizeof(char));
		memcpy(buf, data, dataLen);

		// 1. Assert that encrypted bytes differ
		encrypt(key, keyLen, buf, dataLen);
		if (memcmp(buf, data, dataLen) == 0) {
			printf("[V] Round %lld: FAILED. Encrypted bytes match plaintext.\n", i);
			printf("\tKey: "); hexdump(key, keyLen); printf("\n");
			printf("\tPlaintext: "); hexdump(data, dataLen); printf("\n");
			printf("\tEncrypted: "); hexdump(buf, dataLen); printf("\n");
			return FALSE;
		}

		// 2. Assert that decrypted bytes are the same as original bytes
		decrypt(key, keyLen, buf, dataLen);
		if (memcmp(buf, data, dataLen) != 0) {
			printf("[V] Round %lld: FAILED. Decrypted bytes don't match plaintext.\n", i);
			printf("\tKey: "); hexdump(key, keyLen); printf("\n");
			printf("\tPlaintext: "); hexdump(data, dataLen); printf("\n");
			printf("\tDecrypted: "); hexdump(buf, dataLen); printf("\n");
			return FALSE;
		}

		if (VALIDATION_DEBUG)
			printf("[V] Round %lld: PASSED.\n", i);
	}
	return TRUE;
}