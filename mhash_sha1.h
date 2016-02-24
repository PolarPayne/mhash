#ifndef MHASH_SHA1_H
#define MHASH_SHA1_H

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#include "mhash_utils.h"

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

typedef struct mhash_sha1_ctx {
	uint64_t byte_count;
	uint32_t buffer[80];
	uint32_t state[HASH_LENGTH/4];
	uint8_t buffer_offset;
} mhash_sha1_ctx_type;

void mhash_sha1_init(mhash_sha1_ctx_type*);
void mhash_sha1_writebyte(mhash_sha1_ctx_type*, uint8_t);
void mhash_sha1_write(mhash_sha1_ctx_type*, char*, uint64_t);
void mhash_sha1_result(mhash_sha1_ctx_type*, uint8_t*);

uint8_t* mhash_sha1_file(FILE*);

#endif //MHASH_SHA1_H
