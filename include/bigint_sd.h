/* Serialization + De-serialization functions */
#ifndef __SAMMY_BIGINT_SD_H_INC
#define __SAMMY_BIGINT_SD_H_INC
#include "bigint_defs.h"
#include "bigint_libutil.h"
#include "bigint_mm.h"
#include "customization.h"

/* ===========================[ namespace bigint ]=========================== */

/* get the string representation of the bigint in base 16
 * (heap memory allocation handled by this function; returned value will
 * need to be free()'d) */
char *bigint_tohexstr(const bigint *a);

#endif /* __SAMMY_BIGINT_SD_H_INC */
