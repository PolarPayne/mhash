#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct crc {
    uint64_t crc;
    uint64_t mask;
};

#define MHASH_CRC32 MHASH_CRC_TYPES[0]

static const struct crc MHASH_CRC_TYPES[] =
{
    { 0x00000000EDB88320, 0x00000000ffffffff }
};

uint64_t mhash_crc_buf(struct crc, uint64_t, uint8_t*, size_t);
uint64_t mhash_crc_file(struct crc, FILE*);

#endif // CRC_H
