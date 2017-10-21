#include "bigint_bo.h"

bigint *bigint_lshift(bigint *a, bigint_len_unit n) {
    bigint_len_unit orig_len = a->len;
    /* expand the bigint to provide enough room to lshift
     * the bitshift is in number of bits, so divide by number of
     * bits per unit to know how many units to expand by
     */
    a = bigint_mm_resize(a, a->len + 1 + ((n - 1) / bigint_unit_bits));

    /* for moves greater than 64, we can shift the bytes first then move bits */
    if (n >= 64) {
        /* number of 64-bit -round bytes to move */
        int bc = (n/64)*8;

        /* now we can just do a memmove */
        memmove(
            (uint8_t *)bigint_lu_v(a) + bc, /* destination */
            bigint_lu_v(a), /* source */
            orig_len*sizeof(bigint_unit) /* number of bytes to move */
        );

        /* zero the lower bytes of memory */
        memset(
            bigint_lu_v(a), /* dest */
            0, /* value = 0 */
            bc /* number of bytes */
        );

        n = n % 64;
    }

    /* now we perform the actual bit shifting */
    asm __volatile__ (
        /* use a 64-bit register to store the length of a */
        "movzx r13, %2\n\t"
        /* r14 is the index of current block, r13 is index of left block */
        "dec r13\n\t"
        "mov r14, r13\n\t"

        "bigint_lshift_loop:\n\t"
        /* the last shift is shifting in 0's so treat it differently */
        "test r14, r14\n\t"
        "jz bigint_lshift_final\n\t"
        /* safe to subtract 1 from r13 */
        "dec r13\n\t"
        /* load the next, less significant, block */
        "mov r15, QWORD PTR [%1 + r13*8]\n\t"
        /* shift the bits */
        "shld QWORD PTR [%1 + r14*8], r15, cl\n\t"
        /* decrement r14 */
        "dec r14\n\t"
        /* keep going */
        "jmp bigint_lshift_loop\n\t"

        /* final shift block just shifts in 0's */
        "bigint_lshift_final:\n\t"
        /* get value */
        "mov QWORD PTR [%1], r15\n\t"
        /* shift left */
        "shl r15, cl\n\t"
        /* done; store back */
        "mov QWORD PTR [%1], r15\n\t"
        : 
        /* it is vital that n be in *c since we need register cl */
        : "c"(n), "r"(bigint_lu_v(a)), "r"(a->len)
        : "r13", "r14", "r15", "cc"
    );

    return bigint_mm_optimize(a);
}

bigint *bigint_rshift(bigint *a, bigint_len_unit n) {
    /* for moves greater than 64, we can shift the bytes first then move bits */
    if (n >= 64) {
        /* number of 64-bit -round bytes to move */
        int bc = (n/64)*8;

        /* now we can just do a memmove */
        memmove(
            bigint_lu_v(a), /* destination */
            (uint8_t *)bigint_lu_v(a) + bc, /* source */
            a->len*sizeof(bigint_unit) - bc /* number of bytes to move */
        );

        /* zero the higher bytes of memory */
        memset(
            /* dest */
            (uint8_t *)bigint_lu_v(a) + a->len*sizeof(bigint_unit)-bc,
            0, /* value = 0 */
            bc /* number of bytes */
        );

        n = n % 64;
    }

    /* now we perform the actual bit shifting */
    asm __volatile__ (
        /* use a 64-bit register to store the length of a */
        "movzx r12, %2\n\t"
        /* r13 is the index of current block, r14 is index of right block */
        "xor r13, r13\n\t"
        "xor r14, r14\n\t"

        "bigint_rshift_loop:\n\t"
        /* the last shift is shifting in 0's so treat it differently */
        "inc r14\n\t"
        "cmp r14, r12\n\t"
        "je bigint_rshift_final\n\t"
        /* load the next, more significant, block */
        "mov r15, QWORD PTR [%1 + r14*8]\n\t"
        /* shift the bits */
        "shrd QWORD PTR [%1 + r13*8], r15, cl\n\t"
        /* increment r13 */
        "inc r13\n\t"
        /* keep going */
        "jmp bigint_rshift_loop\n\t"

        /* final shift block just shifts in 0's */
        "bigint_rshift_final:\n\t"
        /* get value */
        "mov QWORD PTR [%1 + r13*8], r15\n\t"
        /* shift right */
        "shr r15, cl\n\t"
        /* done; store back */
        "mov QWORD PTR [%1 + r13*8], r15\n\t"
        : 
        /* it is vital that n be in *c since we need register cl */
        : "c"(n), "r"(bigint_lu_v(a)), "r"(a->len)
        : "r12", "r13", "r14", "r15", "cc"
    );

    return bigint_mm_optimize(a);
}
