.PHONY: run all test clean

BASIC_CFLAGS = -std=c11 -O0 -g
BASIC_LDFLAGS =

ifeq ($(OS),Windows_NT)
	CC = gcc
	BASIC_CFLAGS += -Wall -Wpedantic
else
	CC = clang
	BASIC_CFLAGS += -Weverything
endif

CC = gcc


ALL_CFLAGS = $(CFLAGS) $(BASIC_CFLAGS)
ALL_LDFLAGS = $(LDFLAGS) $(BASIC_LDFLAGS)

BINNAME=mhash
TESTNAME=$(BINNAME)-test

BIN_MAKE_CMD=$(CC) $(ALL_CFLAGS) -o $(BINNAME) $(ALL_LDFLAGS)
TEST_MAKE_CMD=$(CC) $(ALL_CFLAGS) -o $(TESTNAME) $(ALL_LDFLAGS)

all: $(BINNAME)

TEST += test.o
MAIN += main.o

OBJS += mhash_crc32.o
OBJS += mhash_parity.o
OBJS += mhash_md5.o

ALL_OBJS = $(TEST) $(MAIN) $(OBJS)

$(ALL_OBJS): %.o: %.c
	$(CC) -o $*.o -c $(ALL_CFLAGS) $<

$(BINNAME): $(MAIN) $(OBJS)
	$(BIN_MAKE_CMD) $^

test: $(TEST) $(OBJS)
	$(TEST_MAKE_CMD) $^
	@echo
	@time ./$(TESTNAME)

clean:
	rm -rf $(BINNAME) $(TESTNAME)
	rm -rf *.o
