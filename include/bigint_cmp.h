/* Comparison function (less than, greater than, equal to, etc.) */
#ifndef __SAMMY_BIGINT_CMP_H_INC
#define __SAMMY_BIGINT_CMP_H_INC
#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "bigint_mm.h"

#define BIGINT_CMP_LT 4
#define BIGINT_CMP_GT 2
#define BIGINT_CMP_EQ 1

/* ===========================[ namespace bigint ]=========================== */

/* compare a and b - returns BIGINT_CMP_{LT,GT,EQ} */
uint8_t bigint_cmp(const bigint *a, const bigint *b);

#endif /* __SAMMY_BIGINT_CMP_H_INC */
