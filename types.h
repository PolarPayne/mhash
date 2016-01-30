#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * Rust styled naming for integer types.
 * We could use <inttypes.h> but it's just too confusing,
 * for the scope of this project (learning).
 * Also, this isn't meant to be "production" code.
 * Might fail on non 64bit systems?
 */
typedef signed char i8;
typedef unsigned char ui8;
typedef signed short i16;
typedef unsigned short ui16;
typedef signed int i32;
typedef unsigned int ui32;
typedef signed long i64;
typedef unsigned long ui64;

/*
 * Make sure that the types are actually correctly sized.
 */
_Static_assert(CHAR_BIT == 8,  "byte is not 8bits.");

_Static_assert(sizeof(i8) == 1,  "char is not 8bits.");
_Static_assert(sizeof(i16) == 2, "short is not 16bits.");
_Static_assert(sizeof(i32) == 4, "int is not 32bits.");
_Static_assert(sizeof(i64) == 8, "long is not 64bits.");

/*
 * Gets value of bit in nth position.
 * 0 or 1.
 */
#define get_pos(bs,n) _Generic(bs, \
    ui8: _get_pos_ui8,            \
    ui16: _get_pos_ui16,          \
    ui32: _get_pos_ui32,          \
    ui64: _get_pos_ui64           \
    )(bs,n)

ui8 _get_pos_ui8(ui8, ui8);
ui8 _get_pos_ui16(ui16, ui8);
ui8 _get_pos_ui32(ui32, ui8);
ui8 _get_pos_ui64(ui64, ui8);

/*
 * Sets value of bit in nth position to 0 or 1.
 */
#define set_pos(bs,n,v) _Generic(bs, \
    ui8*: _set_pos_ui8,            \
    ui16*: _set_pos_ui16,          \
    ui32*: _set_pos_ui32,          \
    ui64*: _set_pos_ui64           \
    )(bs,n,v)

void _set_pos_ui8(ui8*, ui8, ui8);
void _set_pos_ui16(ui16*, ui8, ui8);
void _set_pos_ui32(ui32*, ui8, ui8);
void _set_pos_ui64(ui64*, ui8, ui8);

#endif // TYPES_H
