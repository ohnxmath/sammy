#include "bigint_sa.h"

bigint *bigint_add(bigint *a, const bigint *b) {
    const bigint *t;
    static bigint_unit msb = (bigint_unit)1 << (bigint_unit_bits - 1);

    /* 
     * if we bigint_add() the same number, we will have memory errors
     * since a could get replaced with a new address... keep track of this
     * and see if a == b.
     */
    t = a;

    /* check if we need to expand length of a */
    if (a->len < b->len) { /* case 1: a < b */
        a = bigint_mm_resize(a, t->len);
    }

    if ((a->len == b->len) && /* case 2: a = b, but addition overflows */
      (bigint_libutil_value(a)[a->len-1] & msb) &&
      (bigint_libutil_value(t)[b->len-1] & msb)) {
        a = bigint_mm_resize(a, a->len + 1);
    }

    /*
     * check if b was equal to old a; if it is, replace it with new a
     * (since old a was free'd)
     */
    if (t == b) b = a;

    asm __volatile__ (
        /* clear counter */
        "xor r15, r15\n\t"
        /* use a 64-bit register to store the length of b */
        "movzx r13, %2\n\t"
        /* load intial block and add them */
        "mov r14, QWORD PTR [%0]\n\t"
        "add r14, QWORD PTR [%1]\n\t"
        /* store back in original value */
        "mov QWORD PTR [%0], r14\n\t"

        /* for loop */
        "bigint_add_nextblock:\n\t"
        /* increment blocks added */
        "inc r15\n\t"
        /* keep the carry flag in ah since cmp will clobber it */
        "lahf\n\t"
        /* ensure in valid bounds for b */
        "cmp r15, r13\n\t"
        "jge bigint_add_done_checkcarry\n\t"
        /* restore carry flag */
        "sahf\n\t"
        /* load next block */
        "mov r14, QWORD PTR [%0 + r15*8]\n\t"
        /* add with carry */
        "adc r14, QWORD PTR [%1 + r15*8]\n\t"
        /* store back */
        "mov QWORD PTR [%0 + r15*8], r14\n\t"
        /* next block */
        "jmp bigint_add_nextblock\n"

        "bigint_add_done_checkcarry:\n\t"
        /* load carry flags */
        "sahf\n\t"
        /* don't access memory beyond if no carry flag set (not safe) */
        "jnc bigint_add_done\n\t"
        /* there was a carry, add it */
        "mov r14, QWORD PTR [%0 + r15*8]\n\t"
        /* adc r14, 0 = just add the carry */
        "adc r14, 0\n\t"
        "mov QWORD PTR [%0 + r15*8], r14\n\t"

        /* all done. */
        "bigint_add_done:\n\t"
        : 
        : "r"(bigint_libutil_value(a)),"r"(bigint_libutil_value(b)),"r"(b->len)
        : "ah", "r13", "r14", "r15", "cc"
    );

    return bigint_mm_optimize(a);
}

bigint *bigint_sub(bigint *a, const bigint *b) {
    uint8_t x;

    /* store the result of compare op in x */
    x = bigint_cmp(a, b);

    if (x == BIGINT_CMP_LT) {
        /* This result is negative! */
        bigint_err_handle(BIGINT_ERR_SUBNEG);
        bigint_free(a);
        return bigint_new(0);
    } else if (x == BIGINT_CMP_EQ) {
        /* This result is zero! */
        bigint_free(a);
        return bigint_new(0);
    }

    /* a->len is > b->len for sure */
    asm __volatile__ (
        /* clear counter */
        "xor r15, r15\n\t"
        /* use a 64-bit register to store the length of b */
        "movzx r13, %3\n\t"
        /* load intial block and subtract them */
        "mov r14, QWORD PTR [%1]\n\t"
        "sub r14, QWORD PTR [%2]\n\t"
        /* store back in original value */
        "mov QWORD PTR [%1], r14\n\t"

        /* for loop */
        "bigint_sub_nextblock:\n\t"
        /* increment blocks added */
        "inc r15\n\t"
        /* keep the carry flag in ah since cmp will clobber it */
        "lahf\n\t"
        /* ensure in valid bounds for b */
        "cmp r15, r13\n\t"
        "jge bigint_sub_done\n\t"
        /* restore carry flag */
        "sahf\n\t"
        /* load next block */
        "mov r14, QWORD PTR [%1 + r15*8]\n\t"
        /* subtract with borrow */
        "sbb r14, QWORD PTR [%2 + r15*8]\n\t"
        /* store back */
        "mov QWORD PTR [%1 + r15*8], r14\n\t"
        /* next block */
        "jmp bigint_sub_nextblock\n"

        "bigint_sub_done:\n\t"
        /* check there was no borrow left over */
        "xor %0, %0\n\t"
        "sahf\n\t"
        "jnc bigint_sub_alldone\n\t"
        "mov %0, 1\n\t"

        "bigint_sub_alldone:\n\t"
        : "=r"(x)
        : "r"(bigint_libutil_value(a)),"r"(bigint_libutil_value(b)),
          "r"(b->len)
        : "ah", "r13", "r14", "r15", "cc"
    );

    /* still need to borrow 1 more */
    if (x == 1) {
        bigint_libutil_value(a)[b->len] -= 1;
    }

    return bigint_mm_optimize(a);
}
