.PHONY: run all test clean mkdirs

CC ::= clang
CFLAGS ::= -std=c11 -Weverything -g -O0 -DDEBUG

OBJ_DIR ::= bin/obj
BIN ::= bin/mhash

run: all
	$(BIN) crc

all: mkdirs main.o types.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/* -o $(BIN)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

types.o: types.c
	$(CC) $(CFLAGS) -c types.c -o $(OBJ_DIR)/types.o

test:
	echo "Nothing to test."

clean:
	rm -rf $(OBJ_DIR)/* $(BIN)

mkdirs:
	mkdir -p $(OBJ_DIR)
