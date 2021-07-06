#ifndef F1F56538_635C_42A3_9E4E_819C1ED1AD69
#define F1F56538_635C_42A3_9E4E_819C1ED1AD69

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>

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

typedef struct _alphabet {
    char symb[CHAR_MAX];
    uint8_t sz;
} Alphabet;

typedef struct _sortaux {
    uint32_t index;
    uint32_t value;
} SortAux;

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

static Alphabet alphabet;
#define COND_INCONDITIONAL 0
#define MAX_AFFIX 4
#define INST_SZ 5
#define HALL_OF_FAME_SZ 100
#define MAX_IT  200000

/* FUNCTIONS */
/* ASSEMBLY */
uint32_t minofthree(uint32_t x, uint32_t y, uint32_t z);

/* C */
static inline char pick_from_alphabet();

int separate(const int p, const int r, SortAux v[]);

void quick_sort_2(const int p, const int r, SortAux v[]);

void quick_sort(const int n, SortAux v[]);

#endif /* F1F56538_635C_42A3_9E4E_819C1ED1AD69 */
