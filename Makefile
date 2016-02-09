.PHONY: run all test clean mkdirs


CC ::= clang
CFLAGS ::= -std=c11 -Weverything -g -O0 -lm

OBJ_DIR ::= bin/obj
BIN ::= bin/mhash


all: mkdirs main.o argparse.o mhash_crc32.o mhash_parity.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/argparse.o $(OBJ_DIR)/mhash_crc32.o $(OBJ_DIR)/mhash_parity.o -o $(BIN)

test: test.o mhash_crc32.o mhash_parity.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/test.o $(OBJ_DIR)/mhash_crc32.o $(OBJ_DIR)/mhash_parity.o -o $(BIN)-test
	time $(BIN)-test

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

argparse.o: argparse.c
	$(CC) -std=c11 -lm -c argparse.c -o $(OBJ_DIR)/argparse.o	

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o $(OBJ_DIR)/test.o

mhash_crc32.o: mhash_crc32.c
	$(CC) $(CFLAGS) -c mhash_crc32.c -o $(OBJ_DIR)/mhash_crc32.o

mhash_parity.o: mhash_parity.c
	$(CC) $(CFLAGS) -c mhash_parity.c -o $(OBJ_DIR)/mhash_parity.o

clean:
	rm -rf $(OBJ_DIR)/* $(BIN)

mkdirs:
	mkdir -p $(OBJ_DIR)
