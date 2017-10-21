/* Definitions for all the types used */
#ifndef __SAMMY_BIGINT_DEFS_H_INC
#define __SAMMY_BIGINT_DEFS_H_INC

/* unsigned long int is guaranteed to be 64 bits (dummy_longsize_check) */
typedef unsigned long int uint64_t;

/* unsigned short is guaranteed to be 8 bits (dummy_charsize_check) */
typedef unsigned char uint8_t;

/* unsigned short is guaranteed to be 16 bits (dummy_shortsize_check) */
typedef unsigned short uint16_t;

/* every block of the bigint is an uint64_t */
typedef uint64_t bigint_unit;

/* max size of the bigint is an array of 2^16 uint64_t's */
typedef uint16_t bigint_len_unit;

/* number of bits in a bigint_unit */
#define bigint_unit_bits 64

/* main bigint structure */
typedef struct bigint {
    bigint_len_unit len;
    /* ... array of uint64_t's (little-endian) goes here ... */
} bigint;

#endif /* __SAMMY_BIGINT_DEFS_H_INC */
