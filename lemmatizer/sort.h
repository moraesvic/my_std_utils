#ifndef E1F972C4_F8A6_44EC_BC10_C190049434F3
#define E1F972C4_F8A6_44EC_BC10_C190049434F3

#include <stdint.h>

typedef struct _sortaux {
    uint32_t index;
    uint32_t value;
} SortAux;

int separate(const int p, const int r, SortAux v[]);

void quick_sort_2(const int p, const int r, SortAux v[]);

void quick_sort(const int n, SortAux v[]);

#endif /* E1F972C4_F8A6_44EC_BC10_C190049434F3 */
