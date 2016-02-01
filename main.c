#include <stdio.h>

#include "types.h"
#include "crc.h"

void test(uint8_t*, size_t, uint64_t);

void test(uint8_t* data, size_t len, uint64_t correct)
{
    ui64 r = mhash_crc_buf(MHASH_CRC32, 0, data, len);
    if (r == correct)
        printf("----MATCH FOUND----\n");
    
    printf("0x%lx <-> 0x%lx\n", r, correct);
}

int main(/*int argc, char* argv[]*/)
{
    // solve cli options and call right options
    // for now, just take input from stdio

    // data = 34ea, polynomial = 0x04C11DB7
    // crc = 0xBA2CEA6E

    uint8_t data1[] = {0x34, 0xea};
    uint64_t c1 = 0xba2cea6e;

    uint8_t data2[] = "hi mom";
    uint64_t c2 = 0xF01CA468;
    
    //uint64_t p = 0x04C11DB7;
    //uint64_t p2 = 0xEDB88320;

    test(data1, 2, c1);
    printf("\n");
    test(data2, 6, c2);


    return 0;
}
