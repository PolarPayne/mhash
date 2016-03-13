#ifndef MHASH_PARITY_H
#define MHASH_PARITY_H

#include <inttypes.h>
#include <stdio.h>

#define MHASH_PARITY_ODD 0
#define MHASH_PARITY_EVEN 1

/* Returns CRC32 hash of data.
 * @crc The current crc of your data (use 0 on first pass).
 * @data Pointer the beginning of your data that will be hashed.
 * @len Length of the data.
 *
 * 
 *
 * @return CRC32 of the data.
 */
uint8_t mhash_parity_buf(uint8_t, uint8_t*, size_t, uint8_t);
uint8_t mhash_parity_file(FILE*, uint8_t);

#endif // MHASH_PARITY_H
