#include <stdio.h>
#include <assert.h>

#include "minunit.h"

#include "mhash_crc32.h"
#include "mhash_parity.h"
#include "mhash_sha1.h"
#include "google_sha1.h"

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

/*
 * CRC32 buffer tests, test values are calculated with
 * two different online calculators to be sure they
 * are correct.
 *
 * Do note that these "strings" don't include null byte.
 */
static char* test_crc32_buf()
{
	uint8_t data[4];
	uint32_t hash;

	data[0] = 'h'; data[1] = 'o'; data[2] = 'w'; data[3] = 'a';
	hash = mhash_crc32_buf(0, data, 4);
	mu_assert("CRC32 of \"howa\" wasn't 0xc6963212", 0xc6963212 == hash);

	data[0] = 'a'; data[1] = 'b'; data[2] = 'c'; data[3] = 'd';
	hash = mhash_crc32_buf(0, data, 4);
	mu_assert("CRC32 of \"abcd\" wasn't 0xed82cd11", 0xed82cd11 == hash);

	data[0] = 'r'; data[1] = 'o'; data[2] = 'n'; data[3] = 'z';
	hash = mhash_crc32_buf(0, data, 4);
	mu_assert("CRC32 of \"ronz\" wasn't 0xe857e51d", 0xe857e51d == hash);

	return 0;
}

static char* test_parity_files()
{
	FILE* fp;
	uint8_t parity;


	fp = fopen("tests/parity0", "rb");
	parity = mhash_parity_file(fp, MHASH_PARITY_EVEN);
	fclose(fp);
	mu_assert("Even parity of parity0 wasn't 1", 1 == parity);

	fp = fopen("tests/parity1", "rb");
	parity = mhash_parity_file(fp, MHASH_PARITY_EVEN);
	fclose(fp);
	mu_assert("Even parity of parity1 wasn't 0", 0 == parity);


	fp = fopen("tests/parity0", "rb");
	parity = mhash_parity_file(fp, MHASH_PARITY_ODD);
	fclose(fp);
	mu_assert("Even parity of parity0 wasn't 0", 0 == parity);

	fp = fopen("tests/parity1", "rb");
	parity = mhash_parity_file(fp, MHASH_PARITY_ODD);
	fclose(fp);
	mu_assert("Even parity of parity1 wasn't 1", 1 == parity);

	return 0;
}

void static print_sha1(uint8_t* h)
{
	for (int i = 0; i < 20; i++) {
		fprintf(stderr, "%02" PRIx8, h[i]);
	}
	fprintf(stderr, "\n");
}

void static print_states(sha1nfo* google, mhash_sha1_ctx_type* mhash)
{
	fprintf(stderr, "---- BUFFER -----\n");
	for (int i = 0; i < 16; i++) {
		fprintf(stderr, "%08" PRIx32 " %08" PRIx32 "\n",
			google->buffer[i], mhash->buffer[i]);
	}
	
	fprintf(stderr, "----- STATE -----\n");
	for (int i = 0; i < 5; i++) {
		fprintf(stderr, "%08" PRIx32 " %08" PRIx32 "\n",
			google->state[i], mhash->state[i]);
	}
}

#define SIZE 256
_Bool static google_vs_mhash(char* filename)
{
	FILE* google_fp = fopen(filename, "rb");
	FILE* mhash_fp = fopen(filename, "rb");

	assert(google_fp != NULL);
	assert(mhash_fp != NULL);

	sha1nfo google;
	mhash_sha1_ctx_type mhash;

	sha1_init(&google);
	mhash_sha1_init(&mhash);

	uint64_t google_c = 0;
	uint64_t mhash_c = 0;

	char google_buffer[SIZE] = {0};
	char mhash_buffer[SIZE] = {0};


	for (
		int k = 0;

		(mhash_c = fread(mhash_buffer, sizeof(uint8_t), SIZE, mhash_fp)) != 0 ||
		(google_c = fread(google_buffer, sizeof(uint8_t), SIZE, google_fp)) != 0;

		k++
	) {
		sha1_write(&google, google_buffer, google_c);
		mhash_sha1_write(&mhash, mhash_buffer, mhash_c);

		fprintf(stderr, "---- PASS %02i ----\n", k);
		print_states(&google, &mhash);
		
	}

	//uint8_t google_res[20];
	//uint8_t mhash_res[20];

	uint8_t* google_res = sha1_result(&google);
	//memcpy(google_res, sha1_result(&google), 20);
	uint8_t* mhash_res = mhash_sha1_result(&mhash);
	//memcpy(mhash_res, mhash_sha1_result(&mhash), 20);

	print_sha1(google_res);
	print_sha1(mhash_res);

	fclose(google_fp);
	fclose(mhash_fp);

	for (int i = 0; i < 20; i++) {
		if (google_res[i] != mhash_res[i])
			return 0;
	}
	return 1;

}

static char* test_sha1()
{
	mu_assert("Google SHA1 and mhash SHA1 output were different",
		google_vs_mhash("tests/fox.txt"));

	return 0;
}

static char* all_tests()
{
	mu_run_test(test_sha1);

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
