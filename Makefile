.PHONY: run all test clean mkdirs


CC ::= clang
CFLAGS ::= -std=c11 -Weverything -g -O0

OBJ_DIR ::= bin/obj
BIN ::= bin/mhash


all: mkdirs main.o crc.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/main.o $(OBJ_DIR)/crc.o -o $(BIN)

test: test.o crc.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/test.o $(OBJ_DIR)/crc.o -o $(BIN)-test
	$(BIN)-test

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o $(OBJ_DIR)/test.o

crc.o: crc.c
	$(CC) $(CFLAGS) -c crc.c -o $(OBJ_DIR)/crc.o

clean:
	rm -rf $(OBJ_DIR)/* $(BIN)

mkdirs:
	mkdir -p $(OBJ_DIR)
