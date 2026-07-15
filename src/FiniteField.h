#ifndef _FINITE_FIELD_H_
#define _FINITE_FIELD_H_

#include <stdint.h>
#include <stdio.h>

typedef long long ff_t;

ff_t FF_mod(ff_t x, ff_t p);
ff_t FF_add(ff_t x0, ff_t x1, ff_t p);
ff_t FF_sub(ff_t x0, ff_t x1, ff_t p);
ff_t FF_mul(ff_t x0, ff_t x1, ff_t p);
ff_t FF_pow(ff_t x, ff_t exp, ff_t p);
ff_t FF_inv(ff_t x, ff_t p);
ff_t FF_div(ff_t x0, ff_t x1, ff_t p);

#endif // _FINITE_FIELD_H_
