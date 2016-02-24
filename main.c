#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "mhash_version.h"
#include "mhash_errors.h"
#include "mhash_crc32.h"
#include "mhash_parity.h"
//#include "mhash_md5.h"
#include "mhash_sha1.h"

void invalid_option(const char*);
void print_help(void);
void print_version(void);

void invalid_option(const char* option)
{
	fprintf(stderr, "mhash: invalid option '%s'\n", option);
	fprintf(stderr, "Try 'mhash --help' for more information\n");
}

void print_help()
{
	fprintf(stderr, "Usage: mhash [OPTION]... [FILE]...\n");
	fprintf(stderr, "Print or check checksums.\n");
	fprintf(stderr, "When no file is present or when file is -, read standard input.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  -b, --binary    read in binary mode\n");
	fprintf(stderr, "  -t, --text      read in text mode\n");
	fprintf(stderr, "  -c, --check     read checksums from the FILEs and check them\n");
	//fprintf(stderr, "      --tag       create BSD-style checksums\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Following options choose which hashing algorithm to use\n");
	fprintf(stderr, "      --even-parity\n");
	fprintf(stderr, "      --odd-parity\n");
	fprintf(stderr, "      --crc32\n");
	fprintf(stderr, "      --md5\n");
	fprintf(stderr, "      --sha1\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "      --help      print this help and exit\n");
	fprintf(stderr, "      --version  print version info and exit\n");
}

void print_version()
{
	fprintf(stderr, "mhash " MHASH_VERSION_STR "\n");
	fprintf(stderr, "Copyright (C) 2016 Maximilian Remming\n");
	fprintf(stderr, "License: ZLib <https://opensource.org/licenses/Zlib>\n");
}

enum hashing_algorithm {
	EVEN_PARITY,
	ODD_PARITY,
	CRC32,
	MD5,
	SHA1
};

int main(const int argc, const char* argv[])
{
	int binary_mode = 0;
	int check = 0;
	int hash = 0;

	// parse options
	for (int i = 1; i < argc; i++) {
		unsigned long len = strlen(argv[i]);

		// argv[i] must start with - to be an option
		if (len == 0 || (len > 0 && argv[i][0] != '-'))
			continue;

		// if the second character is also - then it is a long option
		if (len > 1 && argv[i][1] == '-') {
			if (strcmp("--help", argv[i]) == 0) {
				print_help();
				return 0;
			} else if (strcmp("--version", argv[i]) == 0) {
				print_version();
				return 0;
			} else if (strcmp("--binary", argv[i]) == 0) {
				binary_mode = 1;
			} else if (strcmp("--text", argv[i]) == 0) {
				binary_mode = 0;
			} else if (strcmp("--check", argv[i]) == 0) {
				check = 0;
			} else if (strcmp("--even-parity", argv[i]) == 0) {
				hash = EVEN_PARITY;
			} else if (strcmp("--odd-parity", argv[i]) == 0) {
				hash = ODD_PARITY;
			} else if (strcmp("--crc32", argv[i]) == 0) {
				hash = CRC32;
			} else if (strcmp("--md5", argv[i]) == 0) {
				hash = MD5;
			} else if (strcmp("--sha1", argv[i]) == 0) {
				hash = SHA1;
			} else {
				invalid_option(argv[i]);
				return 1;
			}
			// it can't be a short option
			continue;
		}

		for (unsigned long j = 1; j < len; j++) {
			switch (argv[i][j]) {
			case 'b':
				binary_mode = 1;
				break;
			case 't':
				binary_mode = 0;
				break;
			case 'c':
				check = 1;
				break;
			default:
				invalid_option(argv[i]);
				return 1;
			}
		}
	}

	if (hash == 0) {
		fprintf(stderr, "No hashing algorithm was specified\n");
		fprintf(stderr, "Try 'mhash --help' for more information\n");
		return 1;
	}

	FILE* fp;

	if (check) {
		fprintf(stderr, "file checking is not yet implemented\n");
		return 1;
	} else {
		for (int i = 1; i < argc; i++) {
			unsigned long len = strlen(argv[i]);
			if (len > 0 && argv[i][0] == '-' && len != 1)
				continue;

			char* mode = binary_mode ? "rb" : "r";

			if (len == 1 && argv[i][0] == '-'){
				// make sure that stdin is in right mode
				freopen(NULL, mode, stdin);
				fp = stdin;
			} else {
				fp = fopen(argv[i], mode);
			}

			// switches don't work nicely when values are initialized there
			if (EVEN_PARITY == hash) {
				uint8_t out = mhash_parity_file(fp, MHASH_PARITY_EVEN);
				printf("%" PRIu8, out);
			}
			if (ODD_PARITY == hash) {
				uint8_t out = mhash_parity_file(fp, MHASH_PARITY_ODD);
				printf("%" PRIu8, out);
			}
			if (CRC32 == hash) {
				uint32_t out = mhash_crc32_file(fp);
				printf("%" PRIx32, out);
			}
			if (MD5 == hash) {
				fprintf(stderr, "MD5 not implemented (yet)\n");
				return 1;
			}
			if (SHA1 == hash) {
				uint8_t* out = mhash_sha1_file(fp);
				for (uint8_t j = 0; j < 20; j++)
					printf("%02" PRIx8, out[j]);
				free(out);
			}

			printf("  %s\n", argv[i]);

			fclose(fp);
		}
	}

	return 0;
}
