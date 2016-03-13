#include <stdio.h>

#include "mhash_parity.h"
#include "mhash_crc32.h"
#include "mhash_sha1.h"

void test_parity(int*, int*, uint8_t, uint8_t*, size_t, uint8_t);
void test_parity(int* total, int* fails,
	uint8_t expect, uint8_t* data, size_t len, uint8_t parity)
{
	(*total)++;
	uint8_t result = mhash_parity_buf(0, data, len, parity);
	if (expect != result) {
		(*fails)++;
		printf("=== FAIL ===\n");
		printf("Data:\n\t");
		for (size_t i = 0; i < len; i++) {
			printf("%02" PRIx8, data[i]);
			if ((i+1) % 8 == 0 && (i+1) != len)
				printf("\n\t");
		}
		printf("\n");
	} else {
		printf("=== SUCCESS ===\n");
	}
	printf("Expect: %" PRIu8 "\n", expect);
	printf("Result: %" PRIu8 "\n\n", result);
}

void tests_odd_parity(int*, int*);
void tests_odd_parity(int* total, int* fails)
{
	uint8_t data[64];

	printf("Odd Parity\n");
	printf("==========\n\n");

	for (int i = 0; i < 64; i++)
		data[i] = 0;
	test_parity(total, fails, 1, data, 64, MHASH_PARITY_ODD);

	for (int i = 0; i < 64; i++)
		data[i] = 1;
	test_parity(total, fails, 1, data, 64, MHASH_PARITY_ODD);

	for (int i = 0; i < 64; i++)
		data[i] = 0xff;
	test_parity(total, fails, 1, data, 64, MHASH_PARITY_ODD);

	data[13] = 0;
	test_parity(total, fails, 0, data, 64, MHASH_PARITY_ODD);

	for (int i = 0; i < 64; i++)
		data[i] = 0;
	data[21] = 1;
	test_parity(total, fails, 0, data, 64, MHASH_PARITY_ODD);	
}

void tests_even_parity(int*, int*);
void tests_even_parity(int* total, int* fails)
{
	uint8_t data[64];

	printf("Even Parity\n");
	printf("==========\n\n");

	for (int i = 0; i < 64; i++)
		data[i] = 0;
	test_parity(total, fails, 0, data, 64, MHASH_PARITY_EVEN);

	for (int i = 0; i < 64; i++)
		data[i] = 1;
	test_parity(total, fails, 0, data, 64, MHASH_PARITY_EVEN);

	for (int i = 0; i < 64; i++)
		data[i] = 0xff;
	test_parity(total, fails, 0, data, 64, MHASH_PARITY_EVEN);

	data[13] = 0;
	test_parity(total, fails, 1, data, 64, MHASH_PARITY_EVEN);

	for (int i = 0; i < 64; i++)
		data[i] = 0;
	data[21] = 1;
	test_parity(total, fails, 1, data, 64, MHASH_PARITY_EVEN);	
}

void test_crc32(int*, int*, uint32_t, uint8_t*, size_t);
void test_crc32(int* total, int* fails,
	uint32_t expect, uint8_t* data, size_t len)
{
	(*total)++;
	uint32_t result = mhash_crc32_buf(0, data, len);
	if (expect != result) {
		(*fails)++;
		printf("=== FAIL ===\n");
		printf("Data: ");
		for (size_t i = 0; i < len; i++) {
			printf("%c", (char) data[i]);
		}
		printf("\n");
	} else {
		printf("=== SUCCESS ===\n");
	}
	printf("Expect: %08" PRIx32 "\n", expect);
	printf("Result: %08" PRIx32 "\n\n", result);
}

void tests_crc32(int*, int*);
void tests_crc32(int* total, int* fails)
{
	char* data;

	printf("CRC32\n");
	printf("=====\n\n");

	test_crc32(total, fails, 0, NULL, 0);
	
	data = "hi mom";
	test_crc32(total, fails, 0xf01ca468, (uint8_t*) data, 6);

	data = "The quick brown fox jumps over the lazy dog.";
	test_crc32(total, fails, 0x519025e9, (uint8_t*) data, 44);

	data = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	test_crc32(total, fails, 0x29BA2932, (uint8_t*) data, 56);
}

void printHash(uint8_t* hash) {
	int i;
	for (i=0; i<20; i++) {
		printf("%02x", hash[i]);
	}
	printf("\n");
}

void tests_sha1(int*, int*);
void tests_sha1(int* total, int* fails)
{
	printf("SHA1\n");
	printf("====\n\n");

	mhash_sha1_ctx_type ctx;

	// SHA tests
	printf("Test: FIPS 180-2 C.1 and RFC3174 7.3 TEST1\n");
	printf("Expect: a9993e364706816aba3e25717850c26c9cd0d89d\n");
	printf("Result: ");
	mhash_sha1_init(&ctx);
	mhash_sha1_write(&ctx, "abc", 3);
	printHash(mhash_sha1_result(&ctx));
	printf("\n\n");

	printf("Test: FIPS 180-2 C.2 and RFC3174 7.3 TEST2\n");
	printf("Expect: 84983e441c3bd26ebaae4aa1f95129e5e54670f1\n");
	printf("Result: ");
	mhash_sha1_init(&ctx);
	mhash_sha1_write(&ctx, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56);
	printHash(mhash_sha1_result(&ctx));
	printf("\n\n");

	printf("Test: RFC3174 7.3 TEST4\n");
	printf("Expect: dea356a2cddd90c7a7ecedc5ebb563934f460452\n");
	printf("Result: ");
	mhash_sha1_init(&ctx);
	for (int i = 0; i < 80; i++)
		mhash_sha1_write(&ctx, "01234567", 8);
	printHash(mhash_sha1_result(&ctx));
	printf("\n\n");

	printf("Test: FIPS 180-2 C.3 and RFC3174 7.3 TEST3\n");
	printf("Expect:34aa973cd4c4daa4f61eeb2bdbad27316534016f\n");
	printf("Result:");
	mhash_sha1_init(&ctx);
	for (int i = 0; i < 1000000; i++) mhash_sha1_writebyte(&ctx, 'a');
	printHash(mhash_sha1_result(&ctx));
	printf("\n");
}

int main()
{
	int total = 0;
	int fails = 0;

	tests_odd_parity(&total, &fails);
	tests_even_parity(&total, &fails);
	tests_crc32(&total, &fails);
	tests_sha1(&total, &fails);

	printf("RESULTS\n");
	printf("=======\n");

	float percent = ((float) (total - fails)) / ((float) total);
	printf("%d/%d (%3.2f%%) passed\n", total - fails, total, percent * 100);

	return fails > 0;
}
