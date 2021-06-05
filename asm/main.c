#include <stdio.h>
#include <stdlib.h>

#define M 2000
#define N 14

int friend(int);
int biggest(int*, int);
void selectAsm(int*, int);
void primoAsm(int*, int);

// int fibo(int edi){
//     int eax = 1, ebx = 1, ecx, edx;
//     for(edx = 0; edx < edi; edx++){
//         ecx = eax + ebx;
//         ebx = eax;
//         eax = ecx;
//     }
//     return eax;
// }

int biggest_c (int *v, int n){
    int i, max;
    max = v[0];
    for(i = 0; i < n; i++)
        if(v[i] > max) max = v[i];
    return max;
}

void select_c (int *v, int n){
    int i, min, ind_min, temp;
    if(n == 0) return;
    ind_min = 0;
    min = v[0];
    for(i = 0; i < n; i++)
        if(v[i] < min){
            min = v[i];
            ind_min = i;
        }
    temp = v[0];
    v[0] = min;
    v[ind_min] = temp;
    select_c(v+1, n-1);
}

void print_v(int *v, int n){
    int i;
    for(i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void copy_v(int *u, int *v, int n){
    int i;
    for(i=0;i<n;i++) u[i] = v[i];
}

void primo(int *v, int n){
    int i, j, k;
    if(n == 0) return;
    v[0] = 2;
    if(n == 1) return;
    v[1] = 3;
    for(i = 2; i < n; i++){
        j = v[i-1] + 2;
        for(k = 0; k < i; k++){
            if(v[k] * v[k] >= j)
                break;
            if(j % v[k] == 0){
                j +=2 ;
                k = 0;
            }
        }
    v[i] = j;
    }
}

#define BIG 200

int main(){
    int i, j, k;
    int u[M];
    int v[M];
    
    primo(u, M);
    primoAsm(v, M);
    // print_v(u, M);
    // print_v(v, M);
    

    for(i = 0; i < BIG; i++)
    for(j = 0; j < BIG; j++){
        primo(u, M);
        primoAsm(v, M);
    }
    return 0;
}