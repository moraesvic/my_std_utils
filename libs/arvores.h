#ifndef ARVORES_H
#define ARVORES_H

#include <stdlib.h>
#define MAX(x,y) (x > y ? x : y)

typedef int item;

typedef struct cel {
  item info;
  struct cel * esq;
  struct cel * dir;
} no;

int contaNo(no * raiz);

int altura(no * raiz);

no * busca (no * raiz, int x);

no * maximo (no * raiz);

no * insere (no * raiz, int x);

no * ArvoreRemove (no * raiz, int x);

#endif /* ARVORES_H */
