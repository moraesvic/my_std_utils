#include "lemma.h"

uint32_t levenshtein(char *s1, char *s2) {
    /* https://en.wikibooks.org/wiki/Algorithm_Implementation/Strings/Levenshtein_distance#C */
    uint32_t s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    uint32_t column[s1len + 1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x - 1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = minofthree(column[y] + 1, column[y - 1] + 1,
              lastdiag + (s1[y-1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return column[s1len];
}

uint32_t delete_end(char *s)
{
    uint32_t sz = strlen(s);
    if (sz == 0)
        return EMPTY_STR;
    s[sz - 1] = '\0';
    return OK;
}

uint32_t delete_begin(char *s)
{
    uint32_t i, sz = strlen(s);
    if (sz == 0)
        return EMPTY_STR;
    for (i = 0; i < sz - 1; i++)
        s[i] = s[i + 1];
    s[i] = '\0';
    return OK;
}

/* we assume buffer is large enough ... */

uint32_t insert_end(char *s, char ch)
{
    uint32_t sz = strlen(s);
    s[sz] = ch;
    s[sz + 1] = '\0';
    return OK;
}

uint32_t insert_begin(char *s, char ch)
{
    uint32_t i, sz = strlen(s);
    s[sz + 1] = '\0';
    for (i = sz; i > 0; i--)
        s[i] = s[i - 1];
    s[0] = ch;
    return OK;
}

uint32_t apply_inst(Instruction inst, char * s)
{
    uint32_t ret;
    switch(inst.action) {
    case NO_OP:
        ret = OK;
        break;
    case DEL_END:
        ret = delete_end(s);
        break;
    case DEL_BEGIN:
        ret = delete_begin(s);
        break;
    case INS_END:
        ret = insert_end(s, inst.arg);
        break;
    case INS_BEGIN:
        ret = insert_begin(s, inst.arg);
        break;
    default:
        ret = INST_CODE_INEXISTENT;
    }
    if (ret != OK) 
        fprintf(stderr, "Error applying instruction: %u\n", ret);
    return ret;
}

Instruction gen_inst()
{
    Instruction inst;
    inst.action = randint_mod(LAST_INST);
    if (inst.action == INS_END || inst.action == INS_BEGIN)
        inst.arg = pick_from_alphabet();
    else
        inst.arg = 0;
    return inst;
}

void print_inst(Instruction inst)
{
    printf("%s", INST_NAME[inst.action]);
    if (inst.action == INS_END || inst.action == INS_BEGIN)
        printf("(%c = 0x%02x)", inst.arg, inst.arg);
}

Condition gen_cond()
{
    Condition cond;
    cond.pos = randint_mod(MAX_AFFIX) * rand_sign();
    if (cond.pos != COND_INCONDITIONAL)
        cond.ch = pick_from_alphabet();
    return cond;
}

uint32_t check_condition(Condition cond, char *s)
{
    uint32_t sz;
    if (cond.pos == COND_INCONDITIONAL)
        return 1;
    sz = strlen(s);
    if (abs(cond.pos) > sz)
        return 1;
    if (cond.pos > 0)
        return s[cond.pos + 1] == cond.ch;
    else
        return s[sz + cond.pos] == cond.ch;
}

void print_condition(Condition cond)
{
    printf("IF ");
    if (cond.pos == COND_INCONDITIONAL)
        printf("(1)");
    else
        printf("str[%d] == %c (0x%02x)", cond.pos, cond.ch, cond.ch);
}

FullInst gen_fullinst()
{
    FullInst fi;
    fi.cond = gen_cond();
    fi.inst = gen_inst();
    return fi;
}

void print_fullinst(FullInst fi)
{
    print_condition(fi.cond);
    printf(", THEN ");
    print_inst(fi.inst);
    printf("\n");
}

uint32_t apply_fullinst(FullInst fi, char *s)
{
    uint32_t ret = OK;
    if (check_condition(fi.cond, s))
        ret = apply_inst(fi.inst, s);
    return ret;
}

Indiv *gen_indiv(uint32_t n_genes)
{
    uint32_t i;
    Indiv *indiv = malloc(sizeof(Indiv));
    indiv->score = UINT32_MAX;
    indiv->n_genes = n_genes;
    indiv->fi = malloc(sizeof(FullInst) * n_genes);
    for (i = 0; i < n_genes; i++)
        indiv->fi[i] = gen_fullinst();
    return indiv;
}


void print_indiv(Indiv * indiv, char *deriv)
{
    uint32_t i;
    char write_str[1000];
    strcpy(write_str, deriv);
    printf("SCORE = %u\n", indiv->score);
    printf("INSTRUCTION SET\n\n");
    for (i = 0; i < indiv->n_genes; i++) {
        apply_fullinst(indiv->fi[i], write_str);
        print_fullinst(indiv->fi[i]);
    }
    printf("%s -> %s\n\n", deriv, write_str);
}

void print_pop(Pop *pop, char *deriv)
{
    uint32_t i;

    printf("Population consists of %u individuals\n", pop->sz);
    printf("We have run %u iterations\n", pop->it);
    for (i = 0; i < MAX_PRINT; i++)
        print_indiv(pop->indiv[i], deriv);
}

Pop *gen_pop
(uint32_t sz, uint32_t n_genes, double mut_rate,
double co_rate, double best_perc)
{
    uint32_t i, j;
    Pop *pop = malloc(sizeof(Pop));
    pop->sz = sz;
    pop->mut_thresh = (int)((double)INT_MAX * mut_rate);
    pop->co_thresh = (int)((double)INT_MAX * co_rate);
    pop->best_genes_sz = (int)((double)pop->sz * best_perc);
    pop->it = 0;
    pop->indiv = malloc(sizeof(Indiv *) * pop->sz);
    for (i = 0; i < pop->sz; i++)
        pop->indiv[i] = gen_indiv(n_genes);
    return pop;
}

inline uint32_t run_indiv(Indiv * indiv, char *deriv, char *lemma)
{
    /* returns the fitness score for running a particular set of instructions */
    uint32_t i;
    for (i = 0; i < indiv->n_genes; i++)
        apply_fullinst(indiv->fi[i], deriv);
    indiv->score = levenshtein(deriv, lemma);
    return indiv->score;
}

void run_pop(Pop *pop, char *deriv, char *lemma)
{
    uint32_t i;
    SortAux saux[pop->sz];
    Indiv *tmp[pop->sz];
    char write_str[1000];

    for (i = 0; i < pop->sz; i++) {
        strcpy(write_str, deriv);
        /* break if a perfect set of instructions has been found */
        if(run_indiv(pop->indiv[i], write_str, lemma) == 0)
            break;
    }

    /* sort according to score */

    for (i = 0; i < pop->sz; i++) {
        saux[i].index = i;
        saux[i].value = pop->indiv[i]->score;
    }
    quick_sort(pop->sz, saux);

    for (i = 0; i < pop->sz; i++)
        tmp[i] = pop->indiv[ saux[i].index ];
    for (i = 0; i < pop->sz; i++)
        pop->indiv[i] = tmp[i];

}

uint32_t next_generation(Pop *pop)
{
    uint32_t i, j, n_genes;

    if (pop->indiv[i]->score == 0)
        return 0;

    n_genes = pop->indiv[i]->n_genes;

    for (i = pop->best_genes_sz; i < pop->sz; i++) {
        for (j = 0; j < n_genes; j++)
            pop->indiv[i]->fi[j] = pop->indiv[i % pop->best_genes_sz]->fi[j];
    }

    for (i = pop->best_genes_sz; i < pop->sz; i++)
        for (j = 0; j < n_genes; j++)
            if (rand() < pop->mut_thresh)
                pop->indiv[i]->fi[j] = gen_fullinst();

    pop->it++;
    return 1;
}

int main()
{
    Pop * pop;
    char input[] = "the quick brown fox jumps over the lazy dog";
    char deriv[1000] = "coracoes";
    char lemma[1000] = "coracao";

    time_seed();

    start_alphabet(input);
    print_alphabet();
    pop = gen_pop(1000, N_GENES, MUTATION_RATE, CROSSOVER_RATE,
      BEST_GENES_PERC);

    while (next_generation(pop) && pop->it < MAX_IT) 
        run_pop(pop, deriv, lemma);

    print_pop(pop, deriv);   
    
    return 0;
}