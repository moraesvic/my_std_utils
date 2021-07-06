#include "alphabet.h"

Alphabet ab;

inline uint32_t is_in_alphabet(char ch)
{
    uint32_t i;
    for (i = 0; i < ab.sz; i++)
        if (ab.symb[i] == ch)
            return 1;
    return 0;
}

Alphabet start_alphabet(char *input)
{
    uint32_t i;
    ab.sz = 0;
    for (i = 0; input[i] != 0; i++)
        if (!is_in_alphabet(input[i]))
            ab.symb[ab.sz++] = input[i];
}

void print_alphabet()
{
    uint32_t i;
    printf("Alphabet with %u symbols: ", ab.sz);
    for (i = 0; i < ab.sz; i++)
        printf("%c", ab.symb[i]);
    printf("\n");
}

inline char pick_from_alphabet()
{
    return ab.symb[randint_mod(ab.sz)];
}