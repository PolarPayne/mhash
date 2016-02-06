#include <stdio.h>

#include "minunit.h"

#include "mhash_crc32.h"

int mu_tests_run = 0;

static char* test_crc_derp()
{
	FILE* fp = fopen("tests/derp.png", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of derp.png wasn't 0xac340e73", 0xac340e73 == hash);
    return 0;
}

static char* test_crc_fox()
{
	FILE* fp = fopen("tests/fox.txt", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of fox.txt wasn't 0x519025e9", 0x519025e9 == hash);
    return 0;
}

static char* test_crc_index()
{
	FILE* fp = fopen("tests/index.html", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of index.html wasn't 0xc5813ba0", 0xc5813ba0 == hash);
    return 0;
}

static char* test_crc_mom()
{
	FILE* fp = fopen("tests/mom.txt", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of mom.txt wasn't 0x124f3381", 0x124f3381 == hash);
    return 0;
}

static char* test_crc_random0()
{
	FILE* fp = fopen("tests/random0", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of random0 wasn't 0x124f3381", 0xf60e41de == hash);
    return 0;
}

static char* test_crc_random1()
{
	FILE* fp = fopen("tests/random1", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of random1 wasn't 0xf112b0cb", 0xf112b0cb == hash);
    return 0;
}

static char* test_crc_random2()
{
	FILE* fp = fopen("tests/random2", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of random2 wasn't 0xc06d8a53", 0xc06d8a53 == hash);
    return 0;
}

static char* test_crc_random3()
{
	FILE* fp = fopen("tests/random3", "rb");
	uint64_t hash = mhash_crc_file(fp);
    fclose(fp);

    mu_assert("CRC32 of random3 wasn't 0x41b38c37", 0x41b38c37 == hash);
    return 0;
}

static char* all_tests()
{
    mu_run_test(test_crc_derp);
    mu_run_test(test_crc_fox);
    mu_run_test(test_crc_index);
    mu_run_test(test_crc_mom);
    mu_run_test(test_crc_random0);
    mu_run_test(test_crc_random1);
    mu_run_test(test_crc_random2);
    mu_run_test(test_crc_random3);

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
