# sammy

A BigInteger library written in C (and inline Assembly).

Due to inline assembly and this library relying on very specific behaviours from
x86_64 CPU's, this library is currently not compatible with any other platform
except for x86_64. Future support for arm64 may be considered once the library
has reached a sufficient level of completion :)

## What's done and what's planned
 - [x] Addition
 - [x] Subtraction (underflows are caught and return 0)
 - [x] Comparison
 - [x] Bitshifts
 - [x] Serialization to hex
 - [ ] Creation from string
 - [ ] Multiplication
 - [ ] Division

## A note on speed and efficiency

I wrote this library to learn and have fun! If you want real performance, please
just use the [GNU Multiple Precision](https://gmplib.org) math library instead.

## A note on memory

With very large integers, memory becomes a concern. sammy current calls abort()
upon a memory allocation issue. However, there is an option to use a custom
allocator that will try its best to allocate memory for sammy, even in low-
memory conditions. Please see `include/customization.h` to see how to change
the default allocators.

## Specifications

A bigint is an array of 64-bit unsigned integers. On x86_64, ints are stored
in little endian, and the array of integers is also in little endian - least
significant int first, most significant int last. One 64-bit unsigned integer
will be referred to as a "block" or "qword" (to avoid ambiguity with words in
assembly, which are not 64-bits).

