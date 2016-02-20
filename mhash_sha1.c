#include "mhash_sha1.h"

uint32_t static rol32(uint32_t number, uint8_t bits) {
	return ((number << bits) | (number >> (32-bits)));
}

void static write_byte(struct mhash_sha1_ctx* ctx, uint8_t data)
{
	// Write a single byte
	// If buffer is full hash it
}

uint8_t* mhash_sha1_file(FILE* fp)
{
	assert(fp != NULL);
	return NULL;
}
