#include <stdio.h>

#include "types.h"
#include "crc.h"

void test(ui8*, ui64, ui64, ui64);

void test(ui8* data, ui64 len, ui64 p, ui64 correct)
{
    ui64 r = crc(data, len, p);
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

    ui8 data11[] = {0x34, 0xea};
    ui8 data12[] = {0xae, 0x43};
    ui64 c1 = 0xba2cea6e;

    ui8 data2[] = "hi mom";
    ui64 c2 = 0xF01CA468;
    
    ui64 p = 0x04C11DB7;
    ui64 p2 = 0xEDB88320;

    test(data11, 2, p, c1);
    test(data11, 2, p2, c1);
    test(data12, 2, p, c1);
    test(data12, 2, p2, c1);
    printf("\n");
    test(data2, 5, p, c2);
    test(data2, 5, p2, c2);
    test(data2, 6, p, c2);
    test(data2, 6, p2, c2);
    test(data2, 7, p, c2);
    test(data2, 7, p2, c2);


    return 0;
}
