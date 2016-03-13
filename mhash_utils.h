#ifndef MHASH_UTILS_H
#define MHASH_UTILS_H

#include <stdint.h>

/* Returns true if the machine is big endian.
 *
 * Doesn't rely on undefined behaviour, and works
 * during runtime.
 *
 * @return True on big endian machine, false on
 * little endian.
 */
_Bool mhash_is_big_endian(void);

#endif //MHASH_UTILS_H
