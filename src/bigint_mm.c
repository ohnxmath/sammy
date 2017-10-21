#include "bigint_mm.h"

/* ===========================[ namespace bigint ]=========================== */

bigint *bigint_new(bigint_unit x) {
    /* allocate an initial block of 1 unit */
    bigint *a = bigint_mm_malloc(sizeof(bigint) + sizeof(bigint_unit));
    /* ensure no memory issues */
    if (!a) bigint_mm_err();
    /* set initial length */
    a->len = 1;
    bigint_libutil_value(a)[0] = x;

    return a;
}

bigint *bigint_dup(bigint *a) {
    /* allocate required memory */
    bigint *b = bigint_mm_malloc(sizeof(bigint) + sizeof(bigint_unit) * a->len);
    /* ensure no memory issues */
    if (!b) bigint_mm_err();
    /* copy over data */
    memcpy(b, a, sizeof(bigint) + sizeof(bigint_unit) * a->len);

    return b;
}

void bigint_free(bigint *a) {
    /* simple free */
    bigint_mm_free(a);
}

/* =========================[ namespace bigint_mm ]========================= */

bigint *bigint_mm_optimize(bigint *a) {
    bigint_len_unit i;

    /* first, we want the position of the most significant qword */

    /* need to keep i above 0 to prevent underflow */
    for (i = a->len; i > 0; i--) {
        if (bigint_libutil_value(a)[i-1] == 0) continue;
        break;
    }

    /* i now contains the byte with the most significant non-zero block,
     * so we can remove all the blocks after that one!
     */
    return bigint_mm_resize(a, i);
}

bigint *bigint_mm_resize(bigint *a, bigint_len_unit n) {
    /* ensure there is a change in memory size */
    if (a->len == n) return a;

    /* realloc call */
    a = bigint_mm_realloc(a, sizeof(bigint) + sizeof(bigint_unit) * n);

    /* ensure no memory errors */
    if (!a) bigint_mm_err();

    /* since bigint array is in LSB, we don't need to shuffle memory! :D */

    /* initialize all the new blocks */
    if (a->len < n)
        memset(bigint_libutil_value(a)+a->len,0,(n-a->len)*sizeof(bigint_unit));

    /* new length */
    a->len = n;

    return a;
}

void bigint_mm_err() {
    fprintf(stderr, "! Out Of Memory\n");
    fflush(stderr);
    abort();
}
