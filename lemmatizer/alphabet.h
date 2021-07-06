#ifndef B6CE5A45_6570_4CA0_924D_07820BFC41DE
#define B6CE5A45_6570_4CA0_924D_07820BFC41DE

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "rand.h"

typedef struct _alphabet {
    char symb[CHAR_MAX];
    uint8_t sz;
} Alphabet;

/* */

extern Alphabet ab;

/* */

uint32_t is_in_alphabet(char ch);

Alphabet start_alphabet(char *input);

void print_alphabet();

char pick_from_alphabet();

#endif /* B6CE5A45_6570_4CA0_924D_07820BFC41DE */
