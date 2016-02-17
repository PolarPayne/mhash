#include "mhash_crc32.h"

#define CRC32_POL 0xedb88320

int static inline mhash_crc32(uint32_t* crc, uint8_t data)
{
	uint32_t rem = ~*crc;
	for (size_t bit = 0; bit < 8; bit++) {
		if ((rem & 0x1) != ((data>>bit) & 0x1)) {
			rem = (rem >> 1) ^ (CRC32_POL);
		} else {
			rem = rem >> 1;
		}
	}
	*crc = ~rem;
	return MHASH_OK;
}

int mhash_crc32_buf(uint32_t* crc, uint8_t* data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		if (mhash_crc32(&crc, data[i]) != MHASH_OK)
			return MHASH_ERROR;
	}
	return MHASH_OK;
}

int mhash_crc32_file(FILE* fp, uint32_t* result)
{
	if (fp == NULL || result == NULL)
		return MHASH_NULLPOINTER;

	uint8_t buffer[MHASH_READBUFFER_SIZE];
	int c;

	uint32_t crc = 0;

	size_t i = 0;
	while ((c = fgetc(fp)) != EOF) {
		buffer[i] = (uint8_t) c;
		i++;
		if (i == MHASH_READBUFFER_SIZE) {
			mhash_crc32_buf(&crc, buffer, MHASH_READBUFFER_SIZE);
			i = 0;
		}
	}
	if (i > 0)
		mhash_crc32_buf(&crc, buffer, i);

	return MHASH_OK;
}
