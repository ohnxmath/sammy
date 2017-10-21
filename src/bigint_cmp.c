#include "bigint_cmp.h"

uint8_t bigint_cmp(const bigint *a, const bigint *b) {
    bigint_len_unit i;

    /* first compare lengths */
    if (a->len != b->len)
        return a->len < b->len ? BIGINT_CMP_LT : BIGINT_CMP_GT;

    /* now compare values */
    /* since i is unsigned, we need to be careful of roll-arounds
     * when subtracting 1 from 0, so we ensure we always stay positive
     * by forcing i > 0 before i--
     */
    for (i = a->len; i > 0; i--)
        if (bigint_libutil_value(a)[i-1] != bigint_libutil_value(b)[i-1])
            return bigint_libutil_value(a)[i-1] < bigint_libutil_value(b)[i-1] ?
                BIGINT_CMP_LT : BIGINT_CMP_GT;

    /* everything is equal if we fall through to here */
    return BIGINT_CMP_EQ;
}
