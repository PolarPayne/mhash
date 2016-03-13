#ifndef MHASH_VERSION_H
#define MHASH_VERSION_H

/* High 16 bits is major number, low 16 bits
 * is minor number. Allows easy version number
 * comparisions.
 */
#define MHASH_VERSION_HEX 0x00000001

/* Major version number.
 *
 * Increased when API is broken, or when I
 * just feel like it should be.
 */
#define MHASH_VERSION_MAJOR 0

/* Minor version number.
 *
 * Increased with each smaller release, when
 * bugs are fixed or small new features are
 * added (aka no API breaking stuff).
 */
#define MHASH_VERSION_MINOR 1

/* Version number as a string.
 *
 * You know... When you want to show it to the
 * user or something??
 */
#define MHASH_VERSION_STR "0.1"

#endif // MHASH_VERSION_H
