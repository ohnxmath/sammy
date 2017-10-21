#include "bigint_serialize.h"

char *bigint_rep_stringhex(const bigint *a) {
    char *hex, *nbr;
    int j;

    /* allocate required memory + 0x + null */
    hex = bigint_mm_malloc(16*a->len + 3);
    if (!hex) bigint_mm_err();

    /* terminating null */
    hex[16*a->len+2] = 0;

    /* initial 0x */
    hex[0] = '0';
    hex[1] = 'x';

    nbr = (char *)bigint_libutil_value(a);

    /* loop through all digits */
    for (j = a->len*8; j > 0; j--) {
        hex[j*2] = ((*nbr & 0xF0) >> 4) + '0';
        hex[j*2 + 1] = (*nbr & 0xF) + '0';

        /* adjust for > 9 */
        if (hex[j*2] > '9') hex[j*2] += 7;
        if (hex[j*2+1] > '9') hex[j*2+1] += 7;
        nbr++;
    }

    return hex;
}
