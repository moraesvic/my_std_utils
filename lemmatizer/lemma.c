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

uint32_t insert_end(char *s, char ch)
{
    uint32_t sz = strlen(s);
    if (sz == BUF_SZ - 1)
        return BUF_OVERFLOW;
    s[sz] = ch;
    s[sz + 1] = '\0';
    return OK;
}

uint32_t insert_begin(char *s, char ch)
{
    uint32_t i, sz = strlen(s);
    if (sz == BUF_SZ - 1)
        return BUF_OVERFLOW;
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
#if DEBUG
    if (ret != OK)
        fprintf(stderr, "Error applying instruction: %u\n", ret);
#endif
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
        printf("(1)                 ");
    else {
        if (cond.pos > 0)
            printf("str[+%2d]", cond.pos);
        else
            printf("str[%3d]", cond.pos);
        printf(" == %c (0x%02x)", cond.ch, (unsigned char)cond.ch);
    }
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

uint32_t apply_fullinst(FullInst fi, char *orig, char *s)
{
    uint32_t ret = OK;
    if (check_condition(fi.cond, orig))
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


void print_indiv(Indiv * indiv, Param * param)
{
    uint32_t i;
    printf("INSTRUCTION SET\n\n");
    for (i = 0; i < indiv->n_genes; i++)
        print_fullinst(indiv->fi[i]);
    run_indiv(indiv, param, 1);
}

void print_pop(Pop *pop)
{
    uint32_t i;

    printf("Population consists of %u individuals\n", pop->sz);
    printf("We have run %u iterations\n", pop->it);

    for (i = 0; i < MAX_PRINT; i++) {
        printf("--- INDIVIDUAL %u ---\n\n", i);
        print_indiv(pop->indiv[i], pop->param);
    }
}

void print_pop_short(Pop *pop)
{
    printf("%10u iterations : best score %3u\n", pop->it, pop->indiv[0]->score);
}

Pop *gen_pop
(char **input, char **target, uint32_t param_sz,
uint32_t sz, uint32_t n_genes, double mut_rate,
double co_rate, double best_perc)
{
    uint32_t i, j;
    Pop *pop = malloc(sizeof(Pop));

    pop->param = malloc(sizeof(Param));
    pop->param->input = input;
    pop->param->target = target;
    pop->param->sz = param_sz;

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

uint32_t run_indiv(Indiv * indiv, Param * param, uint32_t print)
{
    /* returns the fitness score for running a particular set of instructions */
    uint32_t i, j, ptl_score;
    char tmp[BUF_SZ];
    indiv->score = 0;

    if (print)
        printf("\n");

    for (i = 0; i < param->sz; i++) {
        strcpy(tmp, param->input[i]);
        for (j = 0; j < indiv->n_genes; j++) {
            apply_fullinst(indiv->fi[j], param->input[i], tmp);
#if DEBUG
            if (print)
                printf("%s\n", tmp);
#endif
        }
        ptl_score = levenshtein(param->target[i], tmp);
        if (print)
            printf("%16s -> %16s (score: %2u)\n", param->input[i], tmp, ptl_score);
        indiv->score += ptl_score;
    }
    if (print)
        printf("SCORE: %2u\n\n", indiv->score);
    return indiv->score;
}

void run_pop(Pop *pop)
{
    uint32_t i;
    SortAux saux[pop->sz];
    Indiv *tmp[pop->sz];

    for (i = 0; i < pop->sz; i++)
        /* break if a perfect set of instructions has been found */
        if(run_indiv(pop->indiv[i], pop->param, 0) == 0)
            break;

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

#include <signal.h>
#include <unistd.h>

Pop * pop;

void interrupt_handler(int signum)
{
    print_pop(pop);
    exit(0);
}

int main()
{
    /*
    char s[] = "amav";
    Instruction inst1 = {DEL_END, 'r'};
    Instruction inst2 = {INS_END, 'r'};
    apply_inst(inst1, s);
    printf("%s\n", s);
    apply_inst(inst2, s);
    printf("%s\n", s);
    return 0;
    */
    signal(SIGINT, interrupt_handler);

    char alphabet[] = "the quick brown fox jumps over the lazy dogçãõ";
    char *input[] = {"amavam", "amar", "amo", "amaria", "vendi", "partir", "casas", "corações", "editores", "carrinho", "pães"};
    char *target[] = {"amar", "amar", "amar", "amar", "vender", "partir", "casa", "coração", "editor", "carro", "pão"};
    uint32_t param_sz = sizeof(input) / sizeof(char*);

    time_seed();

    start_alphabet(alphabet);
    print_alphabet();
    pop = gen_pop(input, target, param_sz, POP_SZ, N_GENES, MUTATION_RATE,
      CROSSOVER_RATE, BEST_GENES_PERC);

    while (next_generation(pop)) {
        run_pop(pop);
        if (pop->it % 100 == 0)
            print_pop_short(pop);
    }

    print_pop(pop);
    
    return 0;
}