#ifndef CRC_H
#define CRC_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#define READBUFFERSIZE 512

struct crc {
    uint64_t pol;
    uint64_t mask;
};

#define MHASH_CRC32 (struct crc){ 0x00000000EDB88320, 0x00000000ffffffff }
#define MHASH_CRC1 (struct crc){ 0x1, 0x1}

uint64_t mhash_crc_buf(struct crc, uint64_t, uint8_t*, size_t);
uint64_t mhash_crc_file(struct crc, FILE*);

#endif // CRC_H
