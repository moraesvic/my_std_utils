#ifndef EP3_H
#define EP3_H

#include <stdio.h>
#include <stdlib.h>

/* vou definir a SEED inicial como meu número USP
   para nossos propósitos, funciona */
#define SEED 8589381
#define PRINT_VETOR  0
#define PRINT_OUTPUT 1
#define PRINT_ORD_IND 1
#define DEBUG 0
#define REPETICOES 16

#define MAX_COUNT_SORT 8192

#define MEDIA_ITENS_URNA 4

#define MAX_ESTRUTURA_PESADA 1024
#define ITENS_ESTRUTURA_PESADA 8

#define DOIS_A_24 16777216
#define DOIS_A_31 2147483648

typedef struct {
    char *nome;
    int n;
    int r_max; /* max range */
    int r_min; /* min range */
    int seed;
} Config;

typedef struct {
    void (*f)( Config, int*, Contador* );
    char *nome;
} Funcao;

typedef struct {
    int a; int b; int c;
    double m; double n;
} Estrutura_Pesada;

void config_start(Config * config, const int n,
                  const int r_max, const int r_min,
                  const int seed);

int maior_que(const int x, const int y, Contador *cont);

int movimenta(int *x, const int y, Contador *cont);

int increase(int *x, Contador *cont);

void print_vetor(const int n, int v[]);

int movimenta(int *x, const int y, Contador *cont);

int increase(int *x, Contador *cont);

void print_vetor(const int n, int v[]);

void selection_sort(const Config config, int v[], Contador *cont);

void bubble_sort(const Config config, int v[], Contador *cont);

void insert_sort(const Config config, int v[], Contador *cont);

void intercala(int p, int q, int r, int v[], Contador *cont);

void merge_sort_2(const int p, const int r, int v[], Contador *cont);

void merge_sort(const Config config, int v[], Contador *cont);

int separa(const int p, const int r, int v[], Contador *cont);

void quick_sort_2(const int p, const int r, int v[], Contador *cont);

void quick_sort(const Config config, int v[], Contador *cont);

void count_sort(const Config config, int v[], Contador *cont);

void radix_sort(const Config config, int v[], Contador *cont);

int ceil_div(int a, int b);

void bucket_sort(const Config config, int v[], Contador *cont);

void zera_vetor(const int n, int v[]);

void concatena_vetor(const int n, const int p,
                     int u[], int v[], int w[], Contador * cont);

void sorteia_vetor(Config config, int v[]);

int * cria_copia_vetor(const int n, int v[]);

void copia_vetor(const int n, int u[], int v[]);

int vetores_iguais(const int n, int u[], int v[]);

void rotina( Funcao func, Config config, int v[]);

int my_assert(Config config, int v[]);

int main();

const Funcao LISTA_FUNCOES[] = 
    {   
        {bubble_sort,    "BubbleSort"   },
        {selection_sort, "SelectSort"   },
        {insert_sort,    "InsertSort"   },
        {merge_sort,     "MergeSort"    },
        {quick_sort,     "QuickSort"    },
        {count_sort,     "CountSort"    },
        {radix_sort,     "RadixSort"    },
        {bucket_sort,    "BucketSort"   }
    };

const int NUM_FUNCOES = 8;

const Config LISTA_DE_TESTES[] =
    {   
        { .nome = "lista media",                 .n = 512,
            .r_max = 4096,          .r_min = 0, .seed = SEED },
        { .nome = "lista minuscula",             .n = 32,
            .r_max = 4096,          .r_min = 0, .seed = SEED },
        { .nome = "lista curta",                 .n = 128,
            .r_max = 4096,          .r_min = 0, .seed = SEED },
        { .nome = "lista longa",                 .n = 1024,
            .r_max = 4096,          .r_min = 0, .seed = SEED },
        { .nome = "lista gigante",               .n = 8192,
            .r_max = 4096,          .r_min = 0, .seed = SEED },
        { .nome = "lista gigante range gigante", .n = 8192,
            .r_max = DOIS_A_24,     .r_min = 0, .seed = SEED },
        { .nome = "lista range minusculo",       .n = 512,
            .r_max = 128,           .r_min = 0, .seed = SEED },
        { .nome = "lista range pequeno",         .n = 512,
            .r_max = 1024,          .r_min = 0, .seed = SEED },
        { .nome = "lista range grande",          .n = 512,
            .r_max = DOIS_A_24,     .r_min = 0, .seed = SEED },
        { .nome = "lista range gigante",         .n = 512,
            .r_max = DOIS_A_31-1,   .r_min = 0, .seed = SEED }
    };

const int NUM_TESTES = 10;

#endif