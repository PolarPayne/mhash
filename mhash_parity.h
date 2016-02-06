#ifndef MHASH_PARITY_H
#define MHASH_PARITY_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#define MHASH_READBUFFER_SIZE 512

#define MHASH_PARITY_EVEN 0
#define MHASH_PARITY_ODD 1

uint8_t mhash_parity_buf(uint8_t, uint8_t*, size_t, uint8_t);
uint8_t mhash_parity_file(FILE*, uint8_t);

#endif // MHASH_PARITY_H
