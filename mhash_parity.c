#include "mhash_parity.h"

/*
 * Precalculated table with even parities
 * of all 8 bit unsigned integers.
 */
static uint8_t parity_table[256] = {
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0,
	0, 1, 1, 0, 1, 0, 0, 1,
	0, 1, 1, 0, 1, 0, 0, 1,
	1, 0, 0, 1, 0, 1, 1, 0
};

uint8_t mhash_parity_buf(uint8_t parity, uint8_t* data, size_t len, uint8_t type)
{
	uint8_t p = data[0];
	for (size_t i = 1; i < len; i++) {
		p ^= data[i];
	}

	return parity ^ (parity_table[p] ^ type);
}

#define BUFFER_LEN 512

uint8_t mhash_parity_file(FILE* fp, uint8_t type)
{
	uint8_t buffer[BUFFER_LEN];
	int c;

	uint8_t parity = 0;

	size_t i = 0;
	while ((c = fgetc(fp)) != EOF) {
		buffer[i] = (uint8_t) c;
		i++;
		if (i == BUFFER_LEN) {
			parity = mhash_parity_buf(parity, buffer, BUFFER_LEN, type);
			i = 0;
		}
	}
	if (i > 0)
		parity = mhash_parity_buf(parity, buffer, i, type);

	return parity;
}
