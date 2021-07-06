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

typedef struct _pop {
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

#define COND_INCONDITIONAL 0
#define MAX_AFFIX 4
#define N_GENES 5
#define HALL_OF_FAME_SZ 100
/* defines the percentage of genes that should be kept in the next generation,
 * when sorted by fitness criterion */
#define BEST_GENES_PERC   0.10
#define MUTATION_RATE     0.125
#define CROSSOVER_RATE    0.0
#define MAX_PRINT 5
#define MAX_IT  10000

/* FUNCTIONS */
/* ASSEMBLY */
uint32_t minofthree(uint32_t x, uint32_t y, uint32_t z);

/* C */


#endif /* F1F56538_635C_42A3_9E4E_819C1ED1AD69 */
