#ifndef CRC_H
#define CRC_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#define READBUFFERSIZE 512

uint32_t mhash_crc_buf(uint32_t, uint8_t*, size_t);
uint32_t mhash_crc_file(FILE*);

#endif // CRC_H
