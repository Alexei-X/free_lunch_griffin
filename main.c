#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Griffin.h"
int main(void)
{
    GriffinVector init_state = { .values = {1, 2, 3} };
    GriffinVector c_1 = { .values = {1234, 125, 232} };

    GriffinVector* one_it =
        round_function(&init_state, &c_1);

    for (int i = 0; i < GRIFFIN_T; i++)
        printf("%lld\n", one_it->values[i]);

    free(one_it);

    return EXIT_SUCCESS;
}

