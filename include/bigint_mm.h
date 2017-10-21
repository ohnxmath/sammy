/* Memory management functions */
#ifndef __SAMMY_BIGINT_MM_H_INC
#define __SAMMY_BIGINT_MM_H_INC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "customization.h"

/* ===========================[ namespace bigint ]=========================== */

/* allocate memory for a new big integer */
bigint *bigint_new(bigint_unit x);

/* duplicate a big integer */
bigint *bigint_dup(bigint *a);

/* free allocated memory */
void bigint_free(bigint *a);

/* =========================[ namespace bigint_mm ]========================= */

/* optimize the memory usage of a bigint (ie, shrink to minimum required mem) */
bigint *bigint_mm_optimize(bigint *a);

/* resize the size of a big integer to n blocks (shrink or enlarge) */
bigint *bigint_mm_resize(bigint *a, bigint_len_unit n);

/* handle a memory allocation error (system out of memory); 
 * this behaviour is decided at compile-time.
 */
void bigint_mm_err();

#endif /* __SAMMY_BIGINT_MM_H_INC */
