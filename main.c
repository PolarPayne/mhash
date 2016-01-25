#include <stdio.h>
#include <string.h>

#include "mhash_errors.h"
#include "mhash_crc.h"

#ifdef DEBUG
#define TRACE(str) printf(str "\n")
#endif

#ifndef DEBUG
#define TRACE(str)
#endif

int main(int argc, char* argv[])
{
    if (argc - 1 < 1) {
        printf("Not enough arguments.");
        return 1;
    }
    // solve cli options and call right options
    return 0;
}
