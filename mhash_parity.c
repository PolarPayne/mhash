#include "mhash_parity.h"

uint8_t static parity_table[UINT8_MAX] = {2};

uint8_t static parity_of(uint8_t data)
{
	if (parity_table[data] == 2) {
		uint8_t c = 0;
		for (uint8_t i = 0; i < 8; i++) {
			c += (data & (1 << i)) >> i;
		}
		parity_table[data] = c % 2;
	}
	return parity_table[data];
}

uint8_t mhash_parity_buf(uint8_t parity, uint8_t* data, size_t len, uint8_t type)
{
	uint8_t p = data[0];
	for (size_t i = 1; i < len; i++) {
		p ^= data[i];
	}

	return parity ^ parity_of(p) ^ type;
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
