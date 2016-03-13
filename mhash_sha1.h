#ifndef MHASH_SHA1_H
#define MHASH_SHA1_H

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mhash_utils.h"

/* Length of the hash in bytes.
 */
#define MHASH_SHA1_LENGTH 20

/* Length of a single block in bytes.
 *
 * Only useful inside the implementation, and when debugging.
 */
#define MHASH_SHA1_BLOCK_LENGTH 64

/* Context that holds all information needed for SHA1.
 *
 * Don't access or change any data except with the right functions.
 */
typedef struct mhash_sha1_ctx {
	uint64_t byte_count;
	uint32_t buffer[MHASH_SHA1_BLOCK_LENGTH/4];
	uint32_t state[MHASH_SHA1_LENGTH/4];
	uint8_t buffer_offset;
} mhash_sha1_ctx_type;

/* Used to initialize the context.
 * @ctx Context to initialize.
 *
 * Allows contexes to be reused.
 */
void mhash_sha1_init(mhash_sha1_ctx_type* ctx);

/* Write a single byte to the context.
 * @ctx Context where to write.
 * @data Byte to write.
 */
void mhash_sha1_writebyte(mhash_sha1_ctx_type* ctx, uint8_t data);

/* Write multiple chars to the context.
 * @ctx Context where to write.
 * @data Pointer to the data.
 * @len Length of the data.
 *
 * Goes through the data, casting it to uint8_t and inserts it to
 * the context with <mhash_sha1_writebyte>.
 */
void mhash_sha1_write(mhash_sha1_ctx_type*, char* data, uint64_t len);

/* Return pointer to the final hash.
 *
 * Do not use the context after calling this function. The pointer
 * will point inside the context, so you'll have to copy it if you
 * wish to use the context again (or if you need it outside of the
 * contexts scope).
 *
 * @return Pointer to the hash (len=20bytes).
 */
uint8_t* mhash_sha1_result(mhash_sha1_ctx_type* ctx);

/* Calcultate the SHA1 sum of given file.
 * @fp File pointer to the file.
 * @res Pointer to an array of size >=20.
 *
 * Reads the file until EOF, and calculates its SHA1 sum, then
 * copies the hash to the pointer.
 */
void mhash_sha1_file(FILE* fp, uint8_t* res);

#endif //MHASH_SHA1_H
