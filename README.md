# mhash
Learning C and hashing algorithms.

# Usage
Example usages:

`./mhash --help`
For the built in help.

`./mhash --even-parity main.c Makefile`
To calculate the even parity of `main.c` and `Makefile`.

`head -c 1M /dev/urandom | ./mhash --crc32 -`
Calculates the CRC32 sum of 1MB of random data (so useful).

# Compiling
`make all` will compile the binary to `./mhash`. You'll need to tinker with the Makefile a bit if you are on Windows or using GCC (changing CC to gcc and removing -Weverything should be anough in most cases).

## Tests
`make test` will compile and run the tests.

# Todo
* Fix SHA1
* More comments (especially for magic values)
* Make public functions work nicer (return error codes etc.)
