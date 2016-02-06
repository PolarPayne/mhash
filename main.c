#include <stdio.h>
#include <string.h>

#include "mhash_crc32.h"
#include "mhash_parity.h"

int main(int argc, char* argv[])
{
	assert(argc >= 2);

	FILE* fp;

	fp = fopen(argv[1], "rb");
	printf("%" PRIx8 "\n", mhash_crc32_file(fp));
	fclose(fp);

	return 0;
}
