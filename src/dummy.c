#define CHAR_BITS 8

static void dummy_funcs_e();

static char dummy_longsize_check() {
    /* ensure long == 64 bits */
    char longcheck[sizeof(unsigned long int)*CHAR_BITS == 64];
    longcheck[0] = 0;
    return *longcheck;
}

static char dummy_charsize_check() {
    /* ensure char == 8 bits */
    char charcheck[sizeof(unsigned char)*CHAR_BITS == 8];
    charcheck[0] = 0;
    return *charcheck;
}

static char dummy_shortsize_check() {
    /* ensure short == 16 bits */
    char shortcheck[sizeof(unsigned short)*CHAR_BITS == 16];
    shortcheck[0] = 0;
    return *shortcheck;
}

static void dummy_funcs() {
    dummy_funcs_e();
    /* dummy functions go under here to prevent unused errors */
    dummy_longsize_check();
    dummy_shortsize_check();
    dummy_charsize_check();
}

/* second function to prevent unused error for dummy_funcs() */
static void dummy_funcs_e() {
    dummy_funcs();
}
