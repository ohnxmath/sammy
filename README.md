# sammy

A simple BigInteger library written in C (and lots of inline Assembly).

## What's done and what's planned
 - [x] Addition
 - [x] Subtraction (underflows are caught and return 0)
 - [x] Comparison
 - [x] Bitshifts
 - [x] Serialization to hex
 - [ ] Creation from hex string
 - [ ] Multiplication
 - [ ] Integer division + Modulo
 - [ ] Header amalgamation into `bigint.h`


## A note on portability

sammy relies heavily on inline assembly for most of its operations
(specifically, x86_64 assembly). As such, sammy is not compatible with any other
platform. Future support for arm64 may be considered once the library has
reached a sufficient level of completion :)

## A note on speed and efficiency

I wrote this library to learn and have fun! If you want real performance, please
just use the [GNU Multiple Precision](https://gmplib.org) math library instead.

## A note on memory

With very large integers, memory becomes a concern. sammy normally calls abort()
upon a memory allocation issue. However, there is an option to use a custom
allocator that will try its best to allocate memory for sammy, even in low-
memory conditions. Please see `include/customization.h` to see how to change
the default allocators.

## Behind-the-scenes

A bigint is an array of 64-bit unsigned integers. On x86_64, ints are stored
in little endian, and the array of integers is also in little endian - least
significant int first, most significant int last. One 64-bit unsigned integer
will be referred to as a "block" or "qword" throughout the code base (to avoid
ambiguity with "word"s in assembly, which are not 64-bits).

## Extensions

sammy as itself is not very useful due to it being restricted purely to unsigned
integers. However, I'm also working on another library which uses sammy to
manipulate integers, but is capable of representing all rational numbers (and
approximates for real numbers). Check it out [here](https://github.com/ohnxmath/taylor)!

## Special thanks to

 - [This x86 ISR](http://x86.renejeschke.de/) - for listing lots of the instructions I needed, and the parameters for each!
 - [Wolfram Cloud](https://sandbox.open.wolframcloud.com) - so I could test to see if the numbers were actually correct
 - [Valgrind](http://valgrind.org/) - for debugging those weird segfaults I had
 - [gdb](https://www.gnu.org/software/gdb/) - for more debugging when I had issues with my assembly code
