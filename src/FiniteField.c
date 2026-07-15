#include "FiniteField.h"

ff_t FF_mod(ff_t x, ff_t p) {
    x %= p;
    if (x < 0)
        x += p;
    return x;
}

ff_t FF_add(ff_t x0, ff_t x1, ff_t p) {
    return FF_mod(FF_mod(x0, p) + FF_mod(x1, p), p);
}

ff_t FF_sub(ff_t x0, ff_t x1, ff_t p) {
    return FF_mod(FF_mod(x0, p) - FF_mod(x1, p), p);
}

ff_t FF_mul(ff_t x0, ff_t x1, ff_t p) {
    __int128 prod = (__int128) FF_mod(x0, p) * FF_mod(x1, p);
    return (ff_t) (prod%p);
}

ff_t FF_pow(ff_t x, ff_t exp, ff_t p) {
    ff_t result = 1;
    x = FF_mod(x, p);
    while (exp > 0) {
        if (exp & 1)
            result = FF_mul(result, x, p);
        x = FF_mul(x, x, p);
        exp >>= 1;
    }
    return result;
}

ff_t FF_inv(ff_t x, ff_t p) {
    if (x % p == 0) {
        printf("x mod p = 0, cannot compute inverse.\n");
        return 0;
    }
    return FF_pow(x, p-2, p);
}

ff_t FF_div(ff_t x0, ff_t x1, ff_t p) {
    return FF_mul(x0, FF_inv(x1, p), p);
}

