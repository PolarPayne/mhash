#include "mhash_crc32.h"

#define CRC32_POL 0xedb88320

uint32_t static inline mhash_crc32(uint32_t crc, uint8_t data)
{
	uint32_t rem = ~crc;
	for (size_t bit = 0; bit < 8; bit++) {
		if ((rem & 0x1) != ((data>>bit) & 0x1)) {
			rem = (rem >> 0x1) ^ (CRC32_POL);
		} else {
			rem = rem >> 0x1;
		}
	}
	return ~rem;
}

uint32_t mhash_crc32_buf(uint32_t crc, uint8_t* data, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		crc = mhash_crc32(crc, data[i]);
	}
	return crc;
}

#define BUFFER_LEN 512

uint32_t mhash_crc32_file(FILE* fp)
{
	uint8_t buffer[BUFFER_LEN];
	int c;

	uint32_t crc = 0;

	size_t i = 0;
	while ((c = fgetc(fp)) != EOF) {
		buffer[i++] = (uint8_t) c;
		if (i == BUFFER_LEN) {
			crc = mhash_crc32_buf(crc, buffer, BUFFER_LEN);
			i = 0;
		}
	}
	if (i > 0)
		crc = mhash_crc32_buf(crc, buffer, i);
	return crc;
}
