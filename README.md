# mhash
Learning C and hashing algorithms.

# Usage
Example usages:
`./mhash --even-parity main.c Makefile`
`head -c 1M /dev/urandom | ./mhash --crc32 -`

`mhash [option]... [file]...`

# Compiling
`make all` will compile the binary to `./mhash`. You'll need to tinker with the Makefile a bit if you are on Windows or use GCC (change CC to gcc and removing -Weverything should be anough in most cases).

# Tests
`make test` will compile and run the tests.

# Todo
* Fix SHA1
* More comments (especially for magic values)
* Make public functions work nicer (return error codes etc.)
