#include "Griffin.h"

uint8_t MDS_matrix[GRIFFIN_T][GRIFFIN_T] = {
    {2, 1, 1},
    {1, 2, 1},
    {1, 1, 2}
};

ff_t deltas[GRIFFIN_T] = {
    666728315538LL,
    516342521089LL,
    386135515175LL
};

ff_t mus[GRIFFIN_T] = {
    167499415962LL,
    903652524989LL,
    384403472705LL
};

static ff_t alpha_inv = -1;

ff_t inv_mod(ff_t a, ff_t m) {
    ff_t t = 0;
    ff_t new_t = 1;

    ff_t r = m;
    ff_t new_r = a;

    while (new_r != 0) {
        ff_t q = r / new_r;

        ff_t tmp;

        tmp = t;
        t = new_t;
        new_t = tmp - q * new_t;

        tmp = r;
        r = new_r;
        new_r = tmp - q * new_r;
    }

    if (r != 1) {
        fprintf(stderr,
                "inv_mod(): inverse does not exist\n");
        exit(EXIT_FAILURE);
    }

    if (t < 0)
        t += m;

    return t;
}

ff_t L_i(ff_t z_0, ff_t z_1, ff_t z_2, int i) {
    ff_t result = FF_add(
            FF_mul((ff_t) (i-1), z_0, GRIFFIN_P),
            FF_add(z_1, z_2, GRIFFIN_P), GRIFFIN_P);
    return result;
}

GriffinVector* NL_layer(GriffinVector* gv) {
    GriffinVector* S = (GriffinVector*) malloc( sizeof(GriffinVector) );
    if (S == NULL) {
        fprintf(stderr,
                "Error allocating memory for S in NL_layer()\n");
        exit(EXIT_FAILURE);
    }
    //S->values = {0, 0, 0};
    if (alpha_inv == -1) alpha_inv = inv_mod(GRIFFIN_ALPHA, GRIFFIN_P-1);
    S->values[0] = FF_pow(gv->values[0], alpha_inv, GRIFFIN_P);
    S->values[1] = FF_pow(gv->values[1], GRIFFIN_ALPHA, GRIFFIN_P);
    ff_t L = L_i(S->values[0], S->values[1], 0, 2);

    ff_t quad =
        FF_add(
            FF_pow(L, 2, GRIFFIN_P),
            FF_add(
                FF_mul(deltas[2], L, GRIFFIN_P),
                mus[2],
                GRIFFIN_P),
            GRIFFIN_P);

    S->values[2] =
        FF_mul(
            gv->values[2],
            quad,
            GRIFFIN_P);

    return S;
}

GriffinVector* MDS_mul(GriffinVector* gv) {
    GriffinVector* out = (GriffinVector*) malloc( sizeof(GriffinVector) );
    if (out == NULL) {
        fprintf(stderr,
                "Error allocating memory for out in MDS_mul()\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < GRIFFIN_T; i++) {
        out->values[i] = 0;
        for (int j = 0; j < GRIFFIN_T; j++) {
            out->values[i] = FF_add(
                        out->values[i],
                        FF_mul(MDS_matrix[i][j], gv->values[j], GRIFFIN_P),
                        GRIFFIN_P
                    );
        }
    }
    return out;
}

GriffinVector* round_function(GriffinVector* gv, GriffinVector* c_i) {
    GriffinVector* S = NL_layer(gv);
    GriffinVector* M = MDS_mul(S);
    GriffinVector* round_result = (GriffinVector*) malloc(sizeof(GriffinVector));
    for (int i = 0; i < GRIFFIN_T; i++) round_result->values[i] = FF_add(M->values[i], c_i->values[i], GRIFFIN_P);
    free(S);
    free(M);
    return round_result;
}

