#ifndef MHASH_CRC32_H
#define MHASH_CRC32_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include "mhash_errors.h"

#define MHASH_READBUFFER_SIZE 512

int mhash_crc32_buf(uint32_t*, uint8_t*, size_t);
int mhash_crc32_file(FILE*, uint32_t*);

#endif // MHASH_CRC32_H
