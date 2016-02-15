#ifndef MHASH_SHA1_H
#define MHASH_SHA1_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <assert.h>

uint8_t* mhash_sha1_buf(uint8_t*, uint64_t);
uint8_t* mhash_sha1_file(FILE*);

//char* mhash_md5_str(uint8_t*);

#endif //MHASH_SHA1_H
