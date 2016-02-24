#include "mhash_sha1.h"

uint32_t static rol32(uint32_t number, uint8_t bits) {
	return ((number << bits) | (number >> (32-bits)));
}

void mhash_sha1_init(mhash_sha1_ctx_type* ctx)
{
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xc3d2e1f0;
	ctx->byte_count = 0;
	ctx->buffer_offset = 0;
}

void static hash_block(mhash_sha1_ctx_type* ctx)
{
	uint32_t a, b, c, d, e, f, k, t;

	a = ctx->state[0];
	b = ctx->state[1];
	c = ctx->state[2];
	d = ctx->state[3];
	e = ctx->state[4];

	for (uint8_t i = 16; i < 80; i++) {
		ctx->buffer[i] = rol32(ctx->buffer[i-3] ^ ctx->buffer[i-8] ^ ctx->buffer[i-14] ^ ctx->buffer[i-16], 1);
	}

	for (uint8_t i = 0; i < 80; i++) {
		if (i < 20) {
			f = (b & c) | (~b & d);
			k = 0x5a827999;
		} else if (i < 40) {
			f = b ^ c ^ d;
			k = 0x6ed9eba1;
		} else if (i < 60) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8f1bbcdc;
		} else {
			f = b ^ c ^ d;
			k = 0xca62c1d6;
		}
		t = rol32(a, 5) + f + e + k + ctx->buffer[i];
		e = d;
		d = c;
		c = rol32(b, 30);
		b = a;
		a = t;
	}
	ctx->state[0] = ctx->state[0] + a;
	ctx->state[1] = ctx->state[1] + b; 
	ctx->state[2] = ctx->state[2] + c;
	ctx->state[3] = ctx->state[3] + d;
	ctx->state[4] = ctx->state[4] + e;

	for (int i = 0; i < 20; i++)
		printf("%02" PRIx8, ((uint8_t*) ctx->state)[i]);
	printf("\n");
}

void static add_uncounted(mhash_sha1_ctx_type* ctx, uint8_t data)
{
	uint8_t* const b = (uint8_t*) ctx->buffer;

	if (mhash_is_big_endian())
		b[ctx->buffer_offset] = data;
	else
		b[ctx->buffer_offset ^ 3] = data;

	(ctx->buffer_offset)++;

	if (ctx->buffer_offset == BLOCK_LENGTH) {
		hash_block(ctx);
		ctx->buffer_offset = 0;
	}
}

void mhash_sha1_writebyte(mhash_sha1_ctx_type* ctx, uint8_t data)
{
	if (++(ctx->byte_count) > (UINT64_MAX / 8)) {
		fprintf(stderr, "too much data to be hashable (max 2^64-1 bits)\n");
		abort();
	}
	add_uncounted(ctx, data);
}

void mhash_sha1_write(mhash_sha1_ctx_type* ctx, char* data, uint64_t len)
{
	for (uint64_t i = 0; i < len; i++)
		mhash_sha1_writebyte(ctx, (uint8_t) data[i]);
}

void static pad(mhash_sha1_ctx_type* ctx)
{
	add_uncounted(ctx, 0x80);
	while (ctx->buffer_offset != 56)
		add_uncounted(ctx, 0x00);

	// SHA1 uses bits, so multiply by 8
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 53));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 45));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 37));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 29));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 21));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 13));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count >> 5));
	add_uncounted(ctx, (uint8_t) (ctx->byte_count << 3));
}

void mhash_sha1_result(mhash_sha1_ctx_type* ctx, uint8_t* res)
{
	pad(ctx);

	if (mhash_is_big_endian()) {
		for (int i = 0; i < 5; i++) {
			ctx->state[i]=
				  (((ctx->state[i])<<24)& 0xff000000)
				| (((ctx->state[i])<<8) & 0x00ff0000)
				| (((ctx->state[i])>>8) & 0x0000ff00)
				| (((ctx->state[i])>>24)& 0x000000ff);
		}
	}

	// Return pointer to hash (20 characters)
	res = (uint8_t*) ctx->state;
}

uint8_t* mhash_sha1_file(FILE* fp)
{
	mhash_sha1_ctx_type ctx;
	mhash_sha1_init(&ctx);

	uint8_t* hash = (uint8_t*) malloc(20);
	char buffer[512];
	uint64_t c = 0;
	while ((c = fread(buffer, sizeof(uint8_t), 512, fp)) != 0)
		mhash_sha1_write(&ctx, buffer, c);

	mhash_sha1_result(&ctx, hash);
	return hash;
}
