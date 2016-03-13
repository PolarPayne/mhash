#ifndef MHASH_PARITY_H
#define MHASH_PARITY_H

#include <inttypes.h>
#include <stdio.h>

/* Type given for the functions when you want odd parity.
 *
 * Parity of data with even amount of 1 bits has odd parity
 * of 1 (after appending the parity bit it has odd amount of
 * 1 bits).
 *
 * Example:
 * data = 1010001
 * count of 1 bits = 3
 * odd parity = 0
 */
#define MHASH_PARITY_ODD 0

/* Type given for the functions when you want even parity.
 *
 * Parity of data with odd amount of 1 bits has even parity
 * of 1 (after appending the parity bit it has even amount of
 * 1 bits).
 *
 * Example:
 * data = 1010001
 * count of 1 bits = 3
 * even parity = 1
 */
#define MHASH_PARITY_EVEN 1

/* Returns parity of data.
 * @crc The current crc of your data (use 0 on first pass).
 * @data Pointer the beginning of your data that will be hashed.
 * @len Length of the data.
 *
 * Calculates the parity of given data.
 *
 * @return Parity of the data.
 */
uint8_t mhash_parity_buf(uint8_t parity, uint8_t* data, size_t len, uint8_t type);

/* Returns parity of file.
 * @fp File pointer to an already open file.
 * @type <MHASH_PARITY_ODD> for odd parity,
 * or <MHASH_PARITY_EVEN> for even parity.
 *
 * Reads the file until EOF and calculates the parity of it.
 *
 * @return Parity of the file.
 */
uint8_t mhash_parity_file(FILE* fp, uint8_t type);

#endif // MHASH_PARITY_H
