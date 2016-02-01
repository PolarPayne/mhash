#include "crc.h"

//ui64 crc(ui8* data, ui64 len, ui64 p)
//{
//	assert(len > 0);
//	ui64 rem = 0;
//	for (ui64 i = 0; i < len; i++) {
//		rem ^= data[i];
//		for (ui8 j = 8; j > 0; j--) {
//			if (rem & 1)
//				rem ^= p;
//			rem >>= 1;
//		}
//	}
//	return rem;
//}

uint64_t static mhash_crc(struct crc type, uint64_t crc, uint8_t* data)
{
	uint64_t rem = (~crc) & type.mask;
	for (size_t bit = 0; bit < 8; bit++) {
        if ((rem & 0x1) != ((*data>>bit) & 0x1)) {
            rem = (rem >> 0x1) ^ (type.crc);
        } else {
            rem = rem >> 0x1;
        }
    }
    return (~rem) & type.mask;
}

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

	uint8_t buffer[512];
	int c;

	while ((c = fgetc(fp)) != EOF) {
       
    }

	return 0;
}
