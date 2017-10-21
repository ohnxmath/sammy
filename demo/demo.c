#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "bigint_bo.h"
#include "bigint_sa.h"
#include "bigint_serialize.h"
#include <stdio.h>

int main() {

    bigint *a = bigint_new(18446744073709551615u);
    bigint *b = bigint_new(18446744073709551615u);
    char *x;
    int i = 0;

    a = bigint_sub(a, b);

    printf("----------------------------------------\n");
    a = bigint_add(a, b);
    a = bigint_add(a, b);
    a = bigint_add(a, b);
    a = bigint_add(a, b);
    a = bigint_add(a, b);

    x = bigint_rep_stringhex(a);
    printf("a = %s\n", x);
    free(x);

    printf("----------------------------------------\n");

    a = bigint_add(a, a);

    x = bigint_rep_stringhex(a);
    printf("a = %s\n", x);
    free(x);

    printf("----------------------------------------\n");

    for (i = 0; i < 10; i++) {
        a = bigint_sub(a, b);
        x = bigint_rep_stringhex(a);
        printf("a = %s\n", x);
        free(x);
    }

    bigint_free(a);
    bigint_free(b);

    printf("----------------------------------------\n");

    a = bigint_new(18446744073709551615u);

    a = bigint_add(a, a);

    b = bigint_lshift(bigint_dup(a), 71);
    x = bigint_rep_stringhex(b);
    printf("a << %02d = %s\n", 71, x);
    free(x);
    bigint_free(b);
    b = bigint_lshift(bigint_dup(a), 72);
    x = bigint_rep_stringhex(b);
    printf("a << %02d = %s\n", 72, x);
    free(x);
    bigint_free(b);

    for (i = 0; i < 10; i++) {
        b = bigint_lshift(bigint_dup(a), i*9);

        x = bigint_rep_stringhex(b);
        printf("a << %02d = %s\n", i*9, x);
        free(x);
        bigint_free(b);
    }

    printf("----------------------------------------\n");

    a = bigint_lshift(a, 50);

    for (i = 0; i < 11; i++) {
        b = bigint_rshift(bigint_dup(a), i*8);

        x = bigint_rep_stringhex(b);
        printf("a >> %02d = %s\n", i*8, x);
        free(x);
        bigint_free(b);
    }

    bigint_free(a);
    return 0;
}
