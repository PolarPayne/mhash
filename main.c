#include <stdio.h>

#include "types.h"

int main(int argc, char* argv[])
{
    if (argc - 1 < 1) {
        printf("Not enough arguments.");
        return 1;
    }
    // solve cli options and call right options
    // for now, just take input from stdio
    ui8 a = 63;
    ui64 b = 0;
    set_pos(&b, a, 1);
    ui8 c = get_pos(b, a);
    printf("%d, 0x%x\n", a, a);
    printf("%lu, 0x%lx\n", b, b);
    printf("%d, 0x%x\n", c, c);
    return 0;
}
