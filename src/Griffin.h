#ifndef _GRIFFIN_H_
#define _GRIFFIN_H_

#include "FiniteField.h"
#include <stdlib.h>

#define GRIFFIN_T     3
#define GRIFFIN_P     922337203687LL
#define GRIFFIN_ALPHA 5

typedef struct GriffinVector {
    ff_t values[GRIFFIN_T];
} GriffinVector;

extern uint8_t MDS_matrix[GRIFFIN_T][GRIFFIN_T];
extern ff_t deltas[GRIFFIN_T];
extern ff_t mus[GRIFFIN_T];

GriffinVector* NL_layer(GriffinVector* gv);
GriffinVector* MDS_mul(GriffinVector* gv);
GriffinVector* round_function(GriffinVector* gv, GriffinVector* c_i);

#endif // _GRIFFIN_H_
