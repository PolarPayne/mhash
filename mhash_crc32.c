#include "mhash_crc32.h"

#define CRC32_POL 0xedb88320

uint32_t static inline mhash_crc32(uint32_t crc, uint8_t data)
{
	uint32_t rem = ~crc;
	for (uint8_t bit = 0; bit < 8; bit++) {
		if ((rem & 0x1) != ((data>>bit) & 0x1)) {
			rem = (rem >> 1) ^ (CRC32_POL);
		} else {
			rem = rem >> 1;
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

uint32_t mhash_crc32_file(FILE* fp)
{
	uint32_t crc = 0;

	uint8_t buffer[512];
	size_t c = 0;
	while (!feof(fp)) {
		c = fread(buffer, sizeof(uint8_t), 512, fp);
		crc = mhash_crc32_buf(crc, buffer, c);
	}

	return crc;
}
