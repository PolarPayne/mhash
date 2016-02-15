#ifndef MHASH_MD5_H
#define MHASH_MD5_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

uint8_t* mhash_md5_buf(uint8_t*, uint32_t);
uint8_t* mhash_md5_file(FILE*);

char* mhash_md5_str(uint8_t*);

#endif //MHASH_MD5_H
