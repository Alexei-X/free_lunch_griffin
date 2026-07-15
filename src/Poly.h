#ifndef _POLY_H_
#define _POLY_H_

#include "FiniteField.h"

#define MAX_VARS 10

typedef struct {
    ff_t coeff;
    uint8_t exp[MAX_VARS];
} Monomial;

typedef struct {
    Monomial *terms;
    size_t n_terms;
} Polynomial;

Polynomial* poly_add(Polynomial* poly1, Polynomial* poly2);
Polynomial* poly_mul(Polynomial* poly1, Polynomial* poly2);

#endif // _POLY_H_
