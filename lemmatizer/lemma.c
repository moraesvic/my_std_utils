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
#if DEBUG_FLAG
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
    else if(inst.action == INIT_IF) {
        inst.pos = (1 + randint_mod(MAX_AFFIX)) * rand_sign();
        inst.arg = pick_from_alphabet();
    } else
        inst.arg = 0;
    return inst;
}

void print_inst(Instruction inst)
{
    printf("%s", INST_NAME[inst.action]);
    if (inst.action == INS_END || inst.action == INS_BEGIN)
        printf("(%c = 0x%02x)", inst.arg, (unsigned char)inst.arg);
    else if (inst.action == INIT_IF) {
        if (inst.pos > 0)
            printf(" str[+%2d]", inst.pos);
        else
            printf(" str[%3d]", inst.pos);
        printf(" == %c (0x%02x)", inst.arg, (unsigned char)inst.arg);
    }
    printf("\n");
}

uint32_t check_condition(Instruction inst, char *s)
{
    uint32_t sz;
    if (inst.action != INIT_IF) {
        printf("xxxxxxxxxxx\n");
        print_inst(inst);
        printf("what are you doing here???\n");
    }

    sz = strlen(s);
    if (abs(inst.pos) > sz)
        return 1;
    if (inst.pos > 0)
        return s[inst.pos + 1] == inst.arg;
    else
        return s[sz + inst.pos] == inst.arg;
}

Indiv *gen_indiv(uint32_t n_genes)
{
    uint32_t i;
    Indiv *indiv = malloc(sizeof(Indiv));
    indiv->score = UINT32_MAX;
    indiv->n_genes = n_genes;
    indiv->inst = malloc(sizeof(Instruction) * n_genes);
    for (i = 0; i < n_genes; i++)
        indiv->inst[i] = gen_inst();
    return indiv;
}

void print_inst_set(Instruction * inst, uint32_t sz)
{
    uint32_t i, j, loopdepth;
    loopdepth = 0;
    printf("INSTRUCTION SET\n\n");
    for (i = 0; i < sz; i++) {
        for (j = 0; j < loopdepth; j++)
            printf("    ");
        print_inst(inst[i]);
        if (inst[i].action == INIT_IF)
            loopdepth++;
        else if (inst[i].action == END_IF && loopdepth > 0)
            loopdepth--;
    }
}

void print_indiv(Indiv * indiv, Param * param)
{
    print_inst_set(indiv->inst, indiv->n_genes);
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

uint32_t run_inst
(Instruction *inst, uint32_t sz, char *orig, char *target, uint32_t print)
{
    uint32_t i, j, score, loopdepth = 0;
    Instruction ifpile[MAX_IF];
    char tmp[BUF_SZ];

#if DEBUG_FLAG
        //print_inst_set(inst, sz);
#endif

    strcpy(tmp, orig);
    for (i = 0; i < sz; i++) {
        // printf("loopdepth: %u\n", loopdepth);
        if (inst[i].action == INIT_IF)
            ifpile[loopdepth++] = inst[i];
        else if (inst[i].action == END_IF && loopdepth > 0)
            loopdepth--;
        else {
            for (j = 0; j < loopdepth; j++)
                if(!check_condition(ifpile[j], orig))
                    goto next_inst;
            apply_inst(inst[i], tmp);
        }
        next_inst:
        ;
#if DEBUG_FLAG
        print_inst(inst[i]);
        printf("%s\n", tmp);
#endif
    }
    score = levenshtein(tmp, target);
    if (print)
        printf("%16s -> %16s (score: %2u)\n", orig, tmp, score);
    return score;
}

uint32_t run_indiv(Indiv * indiv, Param * param, uint32_t print)
{
    /* returns the fitness score for running a particular set of instructions */
    uint32_t i, j, ptl_score;
    indiv->score = 0;

    if (print)
        printf("\n");

    for (i = 0; i < param->sz; i++) {
        ptl_score = run_inst(indiv->inst, indiv->n_genes,
          param->input[i], param->target[i], print);
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
    uint32_t i, j, p, q, n_genes;
    Instruction **tmp;

    if (pop->indiv[0]->score == 0)
        return 0;

    n_genes = pop->indiv[0]->n_genes;

    tmp = malloc(sizeof(Instruction *) * pop->best_genes_sz);
    for (i = 0; i < pop->best_genes_sz; i++)
        tmp[i] = malloc(sizeof(Instruction) * n_genes);

    for (i = 0; i < pop->best_genes_sz; i++)
        for (j = 0; j < n_genes; j++)
            tmp[i][j] = pop->indiv[i]->inst[j];

    /* replicating */
    for (i = 0; i < pop->sz; i+=2) {
        p = randint_mod(pop->best_genes_sz);
        q = randint_mod(pop->best_genes_sz);
        for (j = 0; j < n_genes; j++)
            pop->indiv[i]->inst[j] = tmp[p][j];
        for (j = 0; j < n_genes; j++)
            pop->indiv[i + 1]->inst[j] = tmp[q][j];
        if (rand() > pop->co_thresh) {
            crossover(pop->indiv[p]->inst, pop->indiv[q]->inst, n_genes);
        }
    }

    /* mutating */
    for (i = 0; i < pop->sz; i++)
        for (j = 0; j < n_genes; j++)
            if (rand() < pop->mut_thresh)
                pop->indiv[i]->inst[j] = gen_inst();

    pop->it++;

    for (i = 0; i < pop->best_genes_sz; i++)
        free(tmp[i]);
    free(tmp);

    return 1;
}

#include <signal.h>
#include <unistd.h>

uint32_t interrupt;

void interrupt_handler(int signum)
{
    interrupt = 1;
}

void crossover(Instruction *inst1, Instruction *inst2, uint32_t sz)
{
    uint32_t i, r;
    Instruction tmp;
    r = randint_mod(sz);
    for (i = r; i < sz; i++) {
        tmp = inst1[i];
        inst1[i] = inst2[i];
        inst2[i] = tmp;
    }
}

int main()
{
    /*
    char s[] = "amavamos";
    char goal[] = "amar";
    Instruction inst0 = {INIT_IF, 'a', 1};
    Instruction inst1 = {DEL_END, 'r'};
    Instruction inst2 = {INS_END, 'r'};
    Instruction inst3 = {INIT_IF, 'x', -1};
    Instruction inst4 = {INS_END, 'h'};
    Instruction inst5 = {END_IF,  'h'};
    Instruction inst6 = {DEL_END, 'r'};
    Instruction inst7 = {INS_END, 'r'};
    Instruction inst8 = {END_IF,  'h'};
    Instruction inst9 = {INS_BEGIN, 'A'};
    Instruction instset1[] = {inst0, inst1, inst2, inst3, inst4};
    Instruction instset2[] = {inst5, inst6, inst7, inst8, inst9};
    uint32_t sz = sizeof(instset1) / sizeof(Instruction);
    print_inst_set(instset1, sz);
    print_inst_set(instset2, sz);
    crossover(instset1, instset2, sz);
    print_inst_set(instset1, sz);
    print_inst_set(instset2, sz);
    return 0;
    */
    
    Pop * pop;
    interrupt = 0;
    signal(SIGINT, interrupt_handler);

    char alphabet[] = "the quick brown fox jumps over the lazy dogçãõéVS";
    
    char *input[] =
    {"Vamavam", "Vchamavam", "Vagarravam", "Vlargavam",
    "Vamar", "Vchamar", "Vagarrar", "Vlargar",
    "Vamo", "Vchamo", "Vagarro", "Vlargo",
    "Vamaria", "Vchamaria", "Vagarraria", "Vlargaria",
    "Scasas", "Sasas", "Smalas", "Schamas", "Sgramas",
    "Scorações", "Srações", "Smaldições", "Srazões", "Smelões",
    "Scarrinho", "Sparquinho", "Scachorrinho", "Sgatinho"};
    char *target[] =
    {"Vamar", "Vchamar", "Vagarrar", "Vlargar",
    "Vamar", "Vchamar", "Vagarrar", "Vlargar",
    "Vamar", "Vchamar", "Vagarrar", "Vlargar",
    "Vamar", "Vchamar", "Vagarrar", "Vlargar",
    "Scasa", "Sasa", "Smala", "Schama", "Sgrama",
    "Scoração", "Sração", "Smaldição", "Srazão", "Smelão",
    "Scarro", "Sparque", "Scachorro", "Sgato"};
    
    /*
    char *input[] = {"amavam", "amar", "amo", "amaria", "vendi"};
    char *target[] = {"amar", "amar", "amar", "amar", "vender"};
    */
    uint32_t param_sz = sizeof(input) / sizeof(char*);

    time_seed();

    start_alphabet(alphabet);
    print_alphabet();
    pop = gen_pop(input, target, param_sz, POP_SZ, N_GENES, MUTATION_RATE,
      CROSSOVER_RATE, BEST_GENES_PERC);


    do {
        run_pop(pop);
        if (pop->it % 100 == 0)
            print_pop_short(pop);
    } while (!interrupt && next_generation(pop));

    print_pop(pop);
    
    return 0;
}