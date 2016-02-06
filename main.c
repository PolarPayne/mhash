#include <stdio.h>
#include <string.h>

#include "mhash_crc32.h"

int main(int argc, char* argv[])
{
    assert(argc >= 2);
    FILE* fp = fopen(argv[1], "rb");
    printf("%" PRIx32 "\n", mhash_crc_file(fp));
    fclose(fp);
    return 0;
}
