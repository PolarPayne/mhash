#include <stdio.h>
#include <string.h>

#include "mhash_crc.h"

int main(int argc, char* argv[])
{
    assert(argc >= 2);
    FILE* fp = fopen(argv[1], "rb");
    printf("%" PRIx64 "\n", mhash_crc_file(MHASH_CRC1, fp));
    fclose(fp);
    return 0;
}
