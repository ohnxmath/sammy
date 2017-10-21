/* Simple arithmetic (add, subtract, multiply, truncated divide, modulo) */
#ifndef __SAMMY_BIGINT_SA_H_INC
#define __SAMMY_BIGINT_SA_H_INC
#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "bigint_mm.h"
#include "bigint_cmp.h"
#include "customization.h"

/* ===========================[ namespace bigint ]=========================== */

/* add two bigint's (overwrite value of a; return value of a) */
bigint *bigint_add(bigint *a, const bigint *b);

/* compute a - b (overwrite value of a; return value of a) */
bigint *bigint_sub(bigint *a, const bigint *b);

#endif /* __SAMMY_BIGINT_SA_H_INC */
