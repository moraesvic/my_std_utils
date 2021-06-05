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

#endif /* ARVORES_H */
