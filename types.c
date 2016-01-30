#include "types.h"

ui8 _get_pos_ui8(ui8 bs, ui8 n)
{
    assert(n >= 0 && n < 8);
    return (ui8)((bs & (1 << n)) >> n);
}

ui8 _get_pos_ui16(ui16 bs, ui8 n)
{
    assert(n >= 0 && n < 16);
    return (ui8)((bs & (1 << n)) >> n);
}

ui8 _get_pos_ui32(ui32 bs, ui8 n)
{
    assert(n >= 0 && n < 32);
    return (ui8)((bs & (1 << n)) >> n);
}

ui8 _get_pos_ui64(ui64 bs, ui8 n)
{
    assert(n >= 0 && n < 64);
    return (ui8)((bs & (1 << n)) >> n);
}


void _set_pos_ui8(ui8* bs, ui8 n, ui8 v)
{
	assert(n >= 0 && n < 8);
    assert(v == 0 || v == 1);
}

void _set_pos_ui16(ui16* bs, ui8 n, ui8 v)
{
	assert(n >= 0 && n < 16);
    assert(v == 0 || v == 1);
}

void _set_pos_ui32(ui32* bs, ui8 n, ui8 v)
{
	assert(n >= 0 && n < 32);
    assert(v == 0 || v == 1);
}

void _set_pos_ui64(ui64* bs, ui8 n, ui8 v)
{
	assert(n >= 0 && n < 64);
    assert(v == 0 || v == 1);
}
