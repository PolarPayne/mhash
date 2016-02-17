#ifndef MHASH_ERRORS_H
#define MHASH_ERRORS_H

#include <stdio.h>

enum mhash_error {
	MHASH_OK,
	MHASH_ERROR,
	MHASH_NULLPOINTER
};

char* mhash_get_error(int);

#endif // MHASH_ERRORS_H
