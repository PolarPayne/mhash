#include "mhash_parity.h"

#define VAL_1X 2
#define VAL_2X VAL_1X,  VAL_1X
#define VAL_4X VAL_2X,  VAL_2X
#define VAL_8X VAL_4X,  VAL_4X
#define VAL_16X VAL_8X,  VAL_8X
#define VAL_32X VAL_16X, VAL_16X
#define VAL_64X VAL_32X, VAL_32X
#define VAL_128X VAL_64X, VAL_64X
#define VAL_255X VAL_128X, VAL_64X, VAL_32X, VAL_16X, VAL_8X, VAL_4X, VAL_2X, VAL_1X

uint8_t static parity_table[UINT8_MAX] = {VAL_255X};

uint8_t static parity_of(uint8_t data)
{
	if (parity_table[data] == 2) {
		uint8_t c = 0;
		for (uint8_t i = 0; i < 8; i++) {
			c += (data & (1 << i)) >> i;
		}
		parity_table[data] = c % 2 == 0;
	}
	return parity_table[data];
}

uint8_t mhash_parity_buf(uint8_t parity, uint8_t* data, size_t len, uint8_t type)
{
	uint8_t p = data[0];
	for (size_t i = 1; i < len; i++) {
		p ^= data[i];
	}

	return parity_of(p) ^ type ^ parity;
}

uint8_t mhash_parity_file(FILE* fp, uint8_t type)
{
	uint8_t parity = 0;

	uint8_t buffer[512];
	size_t c = 0;
	while (!feof(fp)) {
		c = fread(buffer, sizeof(uint8_t), 512, fp);
		parity = mhash_parity_buf(parity, buffer, c, type);
	}

	return parity;
}
