.PHONY: run all test clean mkdirs

CC ::= clang
CFLAGS ::= -std=c11 -Weverything -g -O0 -DDEBUG

OBJ_DIR ::= bin/obj
BIN ::= bin/mhash

run: all
	$(BIN) crc

all: mkdirs main.o mhash_errors.o mhash_crc.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/* -o $(BIN)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

mhash_crc.o: mhash_crc.c
	$(CC) $(CFLAGS) -c mhash_crc.c -o $(OBJ_DIR)/mhash_crc.o

mhash_errors.o: mhash_errors.c
	$(CC) $(CFLAGS) -c mhash_errors.c -o $(OBJ_DIR)/mhash_errors.o

test:
	echo "Nothing to test."

clean:
	rm -rf $(OBJ_DIR)/* $(BIN)

mkdirs:
	mkdir -p $(OBJ_DIR)
