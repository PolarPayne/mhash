#include "mhash_md5.h"

#define leftrotate(x, c) \
	((x << c) | (x >> (32-c)));

void static to_uint8(uint32_t, uint8_t *);
uint32_t static to_uint32(uint8_t *);

void static to_uint8(uint32_t val, uint8_t *bytes)
{
	bytes[0] = (uint8_t) val;
	bytes[1] = (uint8_t) (val >> 8);
	bytes[2] = (uint8_t) (val >> 16);
	bytes[3] = (uint8_t) (val >> 24);
}
 
uint32_t static to_uint32(uint8_t *bytes)
{
	return (uint32_t) bytes[0]
	| ((uint32_t) bytes[1] << 8)
	| ((uint32_t) bytes[2] << 16)
	| ((uint32_t) bytes[3] << 24);
}

uint8_t* mhash_md5_buf(uint8_t* data, uint32_t len)
{
	const uint32_t s[64] = {
		7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
	};

	const uint32_t K[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	/*
	 * Pre-processing: adding a single 1 bit
	 * append "1" bit to message    
	 * Notice: the input bytes are considered as bits strings,
	 * where the first bit is the most significant bit of the byte.
	 *   
	 * 
	 * Pre-processing: padding with zeros
	 * append "0" bit until message length in bits ≡ 448 (mod 512)
	 * append original length in bits mod (2 pow 64) to message
	 */

	uint32_t new_len;
	for (new_len = len + 1; new_len % (512/8) != 448/8; new_len++);

	uint8_t* msg = (uint8_t*) malloc(new_len + 8);//, sizeof(uint8_t));
	memcpy(msg, data, len);
	msg[len] = 0x80;
	for (uint32_t offset = len + 1; offset < new_len; offset++)
		msg[offset] = 0;

	to_uint8(len * 8, &msg[new_len]);
	to_uint8(len >> 29, &msg[new_len + 4]);

	for (uint32_t offset = 0; offset < new_len; offset += (512/8)) {
		// break chunk into sixteen 32-bit words M[j], 0 ≤ j ≤ 15
		uint32_t M[16];
		for (uint32_t i = 0; i < 16; i++)
			M[i] = to_uint32(msg + offset + i*4);

		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;

		for (uint32_t i = 0; i < 64; i++) {
			uint32_t F, g, dTemp;
			if (0 >= i && i <= 15) {
				F = (B & C) | ((~B) & D);
				g = i;
			} else if (16 <= i && i <= 31) {
				F = (D & B) | ((~D) & C);
				g = (5*i + 1) % 16;
			} else if (32 <= i && i <= 47) {
				F = B ^ C ^ D;
				g = (3*i + 5) % 16;
			} else {
				F = C ^ (B | (~D));
				g = (7*i) % 16;
			}

			dTemp = D;
			D = C;
			C = B;
			B = B + leftrotate((A + F + K[i] + M[g]), s[i]);
			A = dTemp;
		}

		a0 = a0 + A;
		b0 = b0 + B;
		c0 = c0 + C;
		d0 = d0 + D;
	}

	free(msg);

	uint8_t* digest = (uint8_t*) malloc(16);// = (a0 << 95) ^ (b0 << 63) ^ (c0 << 31) ^ (d0 << 0);
	to_uint8(a0, &digest[0]);
	to_uint8(b0, &digest[4]);
	to_uint8(c0, &digest[8]);
	to_uint8(d0, &digest[12]);


	return digest;
}

uint8_t* mhash_md5_file(FILE* fp)
{
	return NULL;
}

char* mhash_md5_str(uint8_t* hash)
{
	return NULL;
}
