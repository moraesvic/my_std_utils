
#include "my_random.h"

/* DESCRIÇÃO DOS ALGORITMOS */

/*

*    https://stackoverflow.com/questions/11946622/implementation-of-random-number-generator
    
*   https://www.redhat.com/en/blog/understanding-random-number-generators-and-their-limitations-linux

*   https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c


Utilizando os algoritmos descritos acima, muito simples, conseguimos
gerar números pseudo-aleatórios de qualidade. O terceiro link explica
porque tirar o módulo de um número aleatório gerado pode gerar um viés,
e como evitá-lo.

Mas, na verdade, no caso de nossas strings, mesmo 
o mais ingênuo my_randint nos dá tanta uniformidade quanto
o mais sofisticado my_randlong_mod, que toma todos os cuidados
para não ter um intervalo enviesado. Testei com strings de 1M
caracteres, verificando a entropia com "ent" do linux.
Bom, fica a experiência.

O valor da entropia foi calculado em 5.954158 bits por byte,
muito pouco abaixo da entropia da distribuição perfeitamente uniforme,
com entropia de log2(62) = 5.954196 bits por byte
(onde 62 é o número de caracteres que podem estar nas strings)

*/

unsigned int int_seed = SEED_ORIGINAL;
unsigned long long_seed = SEED_ORIGINAL;

unsigned my_randint(){
    int_seed = int_seed * MAGIC_A + MAGIC_B;
    return int_seed;
}

unsigned my_randint_mod(const int mod){
    unsigned end, r;
    if ((mod - 1) == INT_MAX) return my_randint();
    end = INT_MAX / mod;
    end *= mod;
    while( (r = my_randint()) >= end);
    return r % mod;
}

unsigned long my_randlong(){
    long_seed = long_seed * MAGIC_A + MAGIC_B;
    return long_seed;
}

unsigned long my_randlong_mod(const long mod){
    unsigned long end, r;
    if ((mod - 1) == LONG_MAX) return my_randint();
    end = LONG_MAX / mod;
    end *= mod;
    while( (r = my_randlong()) >= end);
    return r % mod;
}

void time_seed(){
    int i;
    int_seed = long_seed = time(NULL);
    for(i = 0; i < SHUFFLE; i++)
    {
        my_randint();
        my_randlong();
    }
}

/* ALGORITMOS DE HASH DE TAMANHO VARIÁVEL (8 a 64 BITS) */

unsigned char hash_char(const char *s){ return hash_long(s) & CHAR_MAX; }

unsigned short hash_short(const char *s){ return hash_long(s) & SHORT_MAX; }

unsigned int hash_int(const char *s){ return hash_long(s) & INT_MAX; }

unsigned long hash_long(const char *s){
    unsigned long h_long = 0;
    while(*s)
        h_long = MULT_31(h_long) + *s++;
    return h_long;
}

/* CRIAÇÃO DE STRING ALEATÓRIA */

char *cria_random_str(const int len){
    char *s = calloc(len, sizeof(char));
    int i;
    /* deixando o último char = \0 */
    for(i = 0; i < len - 1; i++)
    {
        s[i] = my_randlong_mod(TOTAL_RANGE);
        if(s[i] < RANGE_1) s[i] += RANGE_1_START;
        else if(s[i] < RANGE_2) s[i] += RANGE_2_DIFF;
        else if(s[i] < RANGE_3) s[i] += RANGE_3_DIFF;
    }
    return s;
}