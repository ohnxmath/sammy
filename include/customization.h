/* Error handlers */
#ifndef __SAMMY_CUSTOMIZATION_H_INC
#define __SAMMY_CUSTOMIZATION_H_INC
#include <stdio.h>
#include <stdlib.h>

/* =========================[ namespace bigint_err ]========================= */

#define BIGINT_ERR_OOM              70
#define BIGINT_ERR_SUBNEG           19
#define BIGINT_ERR_UNKNOWN          00

/* Handle an error (BIGINT_ERR_*) */
#define bigint_err_handle(code) do {\
            switch (code) {\
            case BIGINT_ERR_OOM:\
                fprintf(stderr, "! Out Of Memory\n");\
                fflush(stderr);\
                abort();\
                break;\
            case BIGINT_ERR_SUBNEG:\
                fprintf(stderr, "! Subtraction result negative\n");\
                break;\
            default:\
                break;\
            }\
        } while (0)

/* =========================[ namespace bigint_mm ]========================== */

/* Allocate memory - returns NULL on failure */
#define bigint_mm_malloc(n)     malloc(n)

/* Reallocate memory - returns NULL on failure */
#define bigint_mm_realloc(x, n) realloc(x, n)

/* Free memory - return value is ignored */
#define bigint_mm_free(x)       free(x)

#endif /* __SAMMY_CUSTOMIZATION_H_INC */
