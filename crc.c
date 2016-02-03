#include "crc.h"

uint64_t static mhash_crc(struct crc type, uint64_t crc, uint8_t* data)
{
	uint64_t rem = (~crc) & type.mask;
	for (size_t bit = 0; bit < 8; bit++) {
        if ((rem & 0x1) != ((*data>>bit) & 0x1)) {
            rem = (rem >> 0x1) ^ (type.pol);
        } else {
            rem = rem >> 0x1;
        }
    }
    return (~rem) & type.mask;
}
size_t t = 0;
uint64_t mhash_crc_buf(struct crc type, uint64_t crc, uint8_t* data, size_t len)
{
	assert(len > 0);

	for (size_t i = 0; i < len; i++) {
		crc = mhash_crc(type, crc, &data[i]);
	}
	return crc;
}

uint64_t mhash_crc_file(struct crc type, FILE* fp)
{
	assert(fp != NULL);

	uint8_t buffer[READBUFFERSIZE];
	int c;

    uint64_t crc = 0;

	size_t i = 0;
	while ((c = fgetc(fp)) != EOF) {
        assert(i >= 0 && i < READBUFFERSIZE);
        buffer[i] = (uint8_t) c;
        i++;
        if (i == READBUFFERSIZE) {
            assert(i == READBUFFERSIZE)
            crc = mhash_crc_buf(type, crc, buffer, READBUFFERSIZE);
            i = 0;
        }
    }
    if (i > 0) {
        assert(i > 0);
        crc = mhash_crc_buf(type, crc, buffer, i);
    }
	return crc;
}
