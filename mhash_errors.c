#include "mhash_errors.h"

char* mhash_get_error(int err)
{
	switch (err) {
	case MHASH_OK:
		return "this is not an error";
	case MHASH_ERROR:
		return "generic error";
	case MHASH_NULLPOINTER:
		return "a null pointer was passed when it wasn't allowed";
	default:
		return "unknown error";
	}
}
