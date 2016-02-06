#include <stdio.h>
#include <string.h>

#include "crc.h"

void print_help(char* arg0)
{
    printf("Usage: %s [OPTION]... [FILE]...\n", arg0);
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
        goto error;
    for (size_t i = 1; i < argc; i++) {
        int l = strlen(argv[i]);
        if (argv[i][0] == '-' && l >= 2) {
            switch (argv[i][1]) {
                case f:
                
            }
        }
    }
    // printf format: HASH_ALGO (FILENAME) = HASH
    return 0;

error:
    print_help();
    return 1;

    //assert(argc >= 2);
    //FILE* fp = fopen(argv[1], "rb");
    //printf("%" PRIx64 "\n", mhash_crc_file(MHASH_CRC1, fp));
    //fclose(fp);
    //return 0;
}
