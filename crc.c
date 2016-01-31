#include "crc.h"

ui64 crc(ui8* data, ui64 len, ui64 p)
{
	assert(len > 0);

	ui64 rem = 0;

	for (ui64 i = 0; i < len; i++) {
		rem ^= data[i];
		for (ui8 j = 8; j > 0; j--) {
			if (rem & 1)
				rem ^= p;
			rem >>= 1;
		}
	}

	return rem;
}
