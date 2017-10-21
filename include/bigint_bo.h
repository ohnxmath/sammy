/* Bit operation functions (shifting, and, or, etc.) */
#ifndef __SAMMY_BIGINT_BITOPS_H_INC
#define __SAMMY_BIGINT_BITOPS_H_INC
#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "bigint_mm.h"
#include <string.h>

/* ===========================[ namespace bigint ]=========================== */

/* shift left a over by n bytes (lossless = integer is expanded to fit) */
bigint *bigint_lshift(bigint *a, bigint_len_unit n);

/* shift right a over by n bytes (lossy = less sig. digits are lost) */
bigint *bigint_rshift(bigint *a, bigint_len_unit n);

#endif /* __SAMMY_BIGINT_BITOPS_H_INC */
