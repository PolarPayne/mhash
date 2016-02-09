#ifndef CRC32_H
#define CRC32_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#define MHASH_READBUFFER_SIZE 512

uint32_t mhash_crc32_buf(uint32_t, uint8_t*, size_t);
uint32_t mhash_crc32_file(FILE*);

#endif // CRC32_H
