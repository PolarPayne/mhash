#ifndef MHASH_SHA1_H
#define MHASH_SHA1_H

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

typedef struct mhash_sha1_ctx {
	uint32_t state[HASH_LENGTH/4];
	uint8_t buffer[BLOCK_LENGTH/4]
	uint64_t byte_count;

} mhash_sha1_ctx_type;

int mhash_sha1_init(mhash_sha1_ctx_type*);
int mhash_sha1_write(mhash_sha1_ctx_type*, const uint8_t*, size_t);
int mhash_sha1_result(mhash_sha1_ctx_type*, uint8_t*);

int mhash_sha1_file(FILE*, uint8_t*);

#endif //MHASH_SHA1_H
