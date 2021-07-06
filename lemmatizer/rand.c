#include "rand.h"

unsigned randint_mod(const int mod)
{
    unsigned end, r;
    if ((mod - 1) == INT_MAX) return rand();
    end = INT_MAX / mod;
    end *= mod;
    while( (r = rand()) >= end);
    return r % mod;
}

int32_t rand_sign()
{
    return (rand() & 1) ? 1 : -1;
}

void time_seed(){ srand(time(NULL)); }