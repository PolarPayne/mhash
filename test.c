#include <stdio.h>

#include "minunit.h"

#include "mhash_crc32.h"

int mu_tests_run = 0;

/*
 * CRC32 file read tests
 */
static char* test_crc32_files()
{
    FILE* fp;
    uint32_t hash;

    fp = fopen("tests/derp.png", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of derp.png wasn't 0xac340e73", 0xac340e73 == hash);

    fp = fopen("tests/fox.txt", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of fox.txt wasn't 0x519025e9", 0x519025e9 == hash);

    fp = fopen("tests/index.html", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of index.html wasn't 0xc5813ba0", 0xc5813ba0 == hash);

    fp = fopen("tests/mom.txt", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of mom.txt wasn't 0x124f3381", 0x124f3381 == hash);

    fp = fopen("tests/random0", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of random0 wasn't 0x124f3381", 0xf60e41de == hash);

    fp = fopen("tests/random1", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of random1 wasn't 0xf112b0cb", 0xf112b0cb == hash);

    fp = fopen("tests/random2", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of random2 wasn't 0xc06d8a53", 0xc06d8a53 == hash);

    fp = fopen("tests/random3", "rb");
    hash = mhash_crc32_file(fp);
    fclose(fp);
    mu_assert("CRC32 of random3 wasn't 0x41b38c37", 0x41b38c37 == hash);

    return 0;
}

static char* test_crc32_buf()
{
    uint8_t data[4] = {'h', 'o', 'w', 'a'};
    uint32_t hash;

    //data = {'h', 'o', 'w', 'a'};
    hash = mhash_crc32_buf(0, data, 4);
    mu_assert("CRC32 of \"howa\" wasn't 0xc6963212", 0xc6963212 == hash);

    return 0;
}

static char* all_tests()
{
    mu_run_test(test_crc32_files);
    mu_run_test(test_crc32_buf);

    return 0;
}

int main()
{
    char* result = all_tests();
    if (result != 0)
        printf("%s\n", result);
    else
        printf("ALL TESTS PASSED\n");

    printf("Tests run: %d\n", mu_tests_run);

    return result != 0;
}
