#ifndef F1F56538_635C_42A3_9E4E_819C1ED1AD69
#define F1F56538_635C_42A3_9E4E_819C1ED1AD69

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#include "sort.h"
#include "rand.h"
#include "alphabet.h"

/* STRUCTS AND TYPEDEFS */

typedef struct _inst {
    uint32_t action;
    char     arg;
} Instruction;

typedef struct _condition {
    int8_t pos;
    char   ch;
} Condition;

typedef struct _fullinst {
    Condition cond;
    Instruction inst;
} FullInst;



typedef struct _indiv {
    uint32_t score;
    uint32_t n_genes;
    FullInst *fi;
} Indiv;

typedef struct _param {
    uint32_t sz;
    char  **input;
    char  **target;
} Param;

typedef struct _pop {
    Param *param;
    uint32_t sz;
    uint32_t best_genes_sz;
    uint32_t mut_thresh;
    uint32_t co_thresh;
    uint32_t it;
    Indiv **indiv;
} Pop;

/* ENUMS */

enum {
    OK        = 0,
    EMPTY_STR,
    BUF_OVERFLOW,
    INST_CODE_INEXISTENT
} ERR;

enum {
    NO_OP    = 0,
    DEL_END,
    DEL_BEGIN,
    INS_END,
    INS_BEGIN,
    LAST_INST
} INST;

static const char *INST_NAME[] = {
    "no-op",
    "del-end",
    "del-begin",
    "ins_end",
    "ins_begin"
};

/* GLOBALS */

#define DEBUG 0

#define COND_INCONDITIONAL 0
#define MAX_AFFIX 4

#define POP_SZ  5000
#define N_GENES 50
#define BEST_GENES_PERC   0.10
#define MUTATION_RATE     0.125
#define CROSSOVER_RATE    0.0

#define MAX_PRINT 5
#define MAX_IT  1000

#define BUF_SZ  128

/* FUNCTIONS */
/* ASSEMBLY */
uint32_t minofthree(uint32_t x, uint32_t y, uint32_t z);

/* C */

Indiv *gen_indiv(uint32_t n_genes);

void print_indiv(Indiv * indiv, Param * param);

void print_pop(Pop *pop);

Pop *gen_pop
(char **input, char **target, uint32_t param_sz,
uint32_t sz, uint32_t n_genes, double mut_rate,
double co_rate, double best_perc);

uint32_t run_indiv(Indiv * indiv, Param * param, uint32_t print);

void run_pop(Pop *pop);

uint32_t next_generation(Pop *pop);


#endif /* F1F56538_635C_42A3_9E4E_819C1ED1AD69 */
