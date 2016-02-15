#include "mhash_sha1.h"

#define leftrotate(x, c) \
	(((x) << (c)) | ((x) >> (32-(c))));

#define bswap_uint64(x)                  \
	((((x) & 0xff00000000000000ull) >> 56)   \
	| (((x) & 0x00ff000000000000ull) >> 40)  \
	| (((x) & 0x0000ff0000000000ull) >> 24)  \
	| (((x) & 0x000000ff00000000ull) >> 8)   \
	| (((x) & 0x00000000ff000000ull) << 8)   \
	| (((x) & 0x0000000000ff0000ull) << 24)  \
	| (((x) & 0x000000000000ff00ull) << 40)  \
	| (((x) & 0x00000000000000ffull) << 56))

uint32_t static rotl32(uint32_t, unsigned int);
void static uint32_to_uint8(uint32_t, uint8_t*);
void static uint64_to_uint8(uint64_t, uint8_t*);
uint32_t static to_uint32(uint8_t*);

uint32_t static rotl32(uint32_t x, unsigned int c)
{
    return (((x) << (c)) | ((x) >> (32-(c))));
}

//uint32_t static rotl32(uint32_t value, unsigned int count)
//{
//    const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
//    count &= mask;
//    return (value<<count) | (value>>( (-count) & mask ));
//}

void static uint32_to_uint8(uint32_t val, uint8_t *bytes)
{
	for (int i = 0; i < 4; i++) {
		bytes[i] = (uint8_t) (val >> i*8);
	}
}

void static uint64_to_uint8(uint64_t val, uint8_t *bytes)
{
	for (int i = 0; i < 8; i++) {
		bytes[i] = (uint8_t) (val >> i*8);
	}
}

uint32_t static to_uint32(uint8_t *bytes)
{
	return (uint32_t) bytes[0]
	| ((uint32_t) bytes[1] << 8)
	| ((uint32_t) bytes[2] << 16)
	| ((uint32_t) bytes[3] << 24);
}

uint8_t* mhash_sha1_buf(uint8_t* data, uint64_t len)
{
	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;
	uint32_t h4 = 0xC3D2E1F0;

	uint64_t new_len = len + (512ul/8ul) - (len % (512ul/8ul));
	//new_len -= sizeof(uint64_t);
	//for (new_len = len + 1; (new_len - sizeof(uint64_t)) % (512/8) != 0; new_len++);
	//new_len++;

	uint8_t* msg = (uint8_t*) calloc(new_len, 1);
	memcpy(msg, data, len);
	msg[len] = 0x80;
	//for (uint64_t offset = len + 1; offset < new_len; offset++)
	//	msg[offset] = 0;

	uint64_to_uint8(len * 8, &msg[new_len - (sizeof(uint64_t))]);//bswap_uint64(len * 8), &msg[new_len - (sizeof(uint64_t))]);

	for (uint64_t offset = 0; offset < new_len; offset += (512/8)) {
		uint32_t w[80];
		for (uint8_t i = 0; i < 16; i++)
			w[i] = to_uint32(&msg[i*sizeof(uint32_t)]);
		for (int i = 16; i < 80; i++) {
			uint32_t tmp = w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16];
			w[i] = rotl32(tmp, 1);
		}

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;

		for (int i = 0; i < 80; i++) {
			uint32_t f, k;
			if (0 <= i && i <= 19) {
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			} else if (20 <= i && i <= 39) {
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			} else if (40 <= i && i <= 59) {
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			} else {
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = rotl32(a, 5) + f + e + k + w[i];
			e = d;
			d = c;
			c = rotl32(b, 30);
			b = a;
			a = temp;
		}

		h0 = h0 + a;
		h1 = h1 + b; 
		h2 = h2 + c;
		h3 = h3 + d;
		h4 = h4 + e;
	}

	free(msg);

	uint8_t* digest = (uint8_t*) malloc(20 * sizeof(uint8_t)); // digest is 160bits wide
	uint32_to_uint8(h0, &digest[0]);
	uint32_to_uint8(h1, &digest[4]);
	uint32_to_uint8(h2, &digest[8]);
	uint32_to_uint8(h3, &digest[12]);
	uint32_to_uint8(h4, &digest[16]);

	return digest;
}

uint8_t* mhash_sha1_file(FILE* fp)
{
	assert(fp != NULL);

	fseek(fp, 0, SEEK_END);
	unsigned long len = (unsigned long) ftell(fp);
	rewind(fp);
	
	/* allocate memory for entire content */
	uint8_t* buffer = calloc(1, len+1);
	if(!buffer) {
		fclose(fp);
		fprintf(stderr, "memory alloc fails\n");
		exit(1);
	}
	
	if(!fread(buffer, len, 1, fp)) {
		fclose(fp);
		free(buffer);
		fprintf(stderr, "entire read fails\n");
		exit(1);
	}
	
	uint8_t* digest = mhash_sha1_buf(buffer, (uint64_t) len);

	free(buffer);

	return digest;
}
