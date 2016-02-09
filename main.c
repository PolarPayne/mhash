#include <stdio.h>
#include <string.h>

#include "argparse.h"

#include "mhash_crc32.h"
#include "mhash_parity.h"

static const char *const usage[] = {
    "test_argparse [options] [[--] args]",
    "test_argparse [options]",
    NULL
};

int main(int argc, char* argv[])
{
	int md5 = 0;
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_GROUP("Hash algorithm options"),
		OPT_BOOLEAN('m', "md5", &md5, "Use MD5"),
		OPT_END()
		/*OPT_HELP(),
		OPT_GROUP("Basic options"),
		OPT_BOOLEAN('f', "force", &force, "force to do"),
		OPT_BOOLEAN('t', "test", &test, "test only"),
		OPT_STRING('p', "path", &path, "path to read"),
		OPT_INTEGER('n', "num", &num, "selected num"),
		OPT_GROUP("Bits options"),
		OPT_BIT(0, "read", &perms, "read perm", NULL, PERM_READ, OPT_NONEG),
		OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE),
		OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC),
		OPT_END(),*/
	};
	struct argparse argparse;
	argparse_init(&argparse, options, usage, 0);
	argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");
	argc = argparse_parse(&argparse, argc, argv);
	if (argc != 0) {
		printf("argc: %d\n", argc);
		int i;
		for (i = 0; i < argc; i++) {
			printf("argv[%d]: %s\n", i, *(argv + i));
		}
	}
	return 0;
}
