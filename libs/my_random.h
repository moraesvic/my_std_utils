#ifndef MY_RANDOM_H
#define MY_RANDOM_H
#include <stdlib.h>
#include <time.h>

extern unsigned int int_seed;
extern unsigned long long_seed;

unsigned my_randint();
unsigned my_randint_mod(const int mod);
unsigned long my_randlong();
unsigned long my_randlong_mod(const long mod);

void time_seed();

#define SHUFFLE 128

/*
   A escolha do multiplicador como um número primo se deve
à sugestão dos links abaixo. Também devo a eles a macro de otimização

*  https://stackoverflow.com/questions/2624192/good-hash-function-for-strings
*  https://computinglife.wordpress.com/2008/11/20/why-do-hash-functions-use-prime-numbers/

 */

#define SEED_ORIGINAL 8589381
#define MULTIPLICADOR 31
#define MULT_31(X) ((X << 5) - X)

/* Maiores valores possíveis para cada um dos tipos */

#define CHAR_MAX  0xffU
#define SHORT_MAX 0xffffU
#define INT_MAX   0xffffffffU
#define LONG_MAX  0xffffffffffffffffU

/* Os magic numbers podem ser compreendidos a partir dos links disponíveis
nos comentários de my_random.c */

#define MAGIC_A 1103515245
#define MAGIC_B 12345

/* ALGORITMOS DE HASH DE TAMANHO VARIÁVEL (8 a 64 BITS) */

unsigned char  hash_char(const char *s);
unsigned short hash_short(const char *s);
unsigned int   hash_int(const char *s);
unsigned long  hash_long(const char *s);

/* CRIAÇÃO DE STRING ALEATÓRIA */

#define ORD_0 48
#define ORD_9 57
#define ORD_A 65
#define ORD_Z 90
#define ORD_a 97
#define ORD_z 122
#define TOTAL_RANGE (ORD_9 - ORD_0 + 1 + \
                     ORD_Z - ORD_A + 1 + \
                     ORD_z - ORD_a + 1)
#define RANGE_1 (ORD_9 - ORD_0 + 1)
#define RANGE_1_START ORD_0
#define RANGE_2 (RANGE_1 + ORD_Z - ORD_A + 1)
#define RANGE_2_START ORD_A
#define RANGE_2_DIFF RANGE_2_START - RANGE_1
#define RANGE_3 (RANGE_2 + ORD_z - ORD_a + 1)
#define RANGE_3_START ORD_a
#define RANGE_3_DIFF RANGE_3_START - RANGE_2

char *cria_random_str(const int len);

#endif