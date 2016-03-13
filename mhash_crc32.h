#ifndef MHASH_CRC32_H
#define MHASH_CRC32_H

#include <inttypes.h>
#include <stdio.h>

/* Returns CRC32 of data.
 * @crc The current crc of your data (use 0 on first pass).
 * @data Pointer to the beginning of your data that will be hashed.
 * @len Length of the data.
 *
 * Calculates the CRC32 of given data.
 *
 * @return CRC32 of the data.
 */
uint32_t mhash_crc32_buf(uint32_t crc, uint8_t* data, size_t len);

/* Returns CRC32 of file.
 * @fp File pointer to an already open file.
 *
 * Reads the file until EOF and hashes the data.
 *
 * @return CRC32 of the file.
 */
uint32_t mhash_crc32_file(FILE* fp);

#endif // MHASH_CRC32_H
