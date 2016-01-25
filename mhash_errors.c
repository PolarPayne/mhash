#include "mhash_errors.h"

void mhash_print_error(int err)
{
    switch (err) {
        case MHASH_OK:
            printf("OK\n");
            break;
        case MHASH_ERROR:
            printf("ERROR\n");
            break;
        default:
            printf("huh!?\n");
            break;
    }
}
