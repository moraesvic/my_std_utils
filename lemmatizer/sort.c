#include "sort.h"

int separate(const int p, const int r, SortAux v[]){
    const SortAux pivot = v[r];
    int j, k;
    SortAux temp;

    for(j = p, k = p; k < r; ++k){
        if(v[k].value <= pivot.value){
            temp = v[j];
            v[j] = v[k];
            v[k] = temp;
            ++j;
        }
    }
    v[r] = v[j];
    v[j] = pivot;

    return j;
}

void quick_sort_2(const int p, const int r, SortAux v[]){
    if(p >= r)
        return;    
    int j;
    j = separate(p, r, v);
    quick_sort_2(p, j-1, v);
    quick_sort_2(j+1, r, v);
}

void quick_sort(const int n, SortAux v[]){
    /* Wrapper */
    quick_sort_2(0, n-1, v);
}