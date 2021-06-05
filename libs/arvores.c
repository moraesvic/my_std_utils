#include "arvores.h"

// obs verificar se a macro acima efetua duas vezes o valor de x e de y
// ou como é possível corrigir isso

int contaNo(no * raiz){
  return raiz == NULL ? 0 : 1 + contaNo(raiz->esq) + contaNo(raiz->dir);
}

int altura(no * raiz){
  return raiz == NULL ? -1 : 1 + MAX(altura(raiz->esq),altura(raiz->dir));
}



/* Busca um elemento na árvore de busca binária

no * busca (no * raiz, int x); 

*/

no * busca (no * raiz, int x){
  if (raiz == NULL || raiz->info == x)
    return raiz;
  if (x < raiz->info)
    return busca (raiz->esq, x);
  return busca (raiz->dir, x);
}  

/* Devolve o máximo de uma ABB

no * maximo (no * raiz); 

*/

no * maximo (no * raiz){
  no * p = raiz;
  while (p != NULL && p->dir != NULL)
    p = p->dir;
  return p;
} 

/* Insere um elemento em uma ABB, devolve a raiz da árvore 
   com o elemento inserido

no * insere (no * raiz, int x); 

*/ 

no * insere (no * raiz, int x){
  if (raiz == NULL){
    raiz = malloc (sizeof(no));
    raiz->info = x;
    raiz->dir = raiz->esq = NULL;
    return raiz;
  }
  if (x < raiz->info)
    raiz->esq = insere (raiz->esq, x);
  else if (x > raiz->info)
    raiz->dir = insere (raiz->dir, x);
  return raiz;
}

/* 

no * remove (no * raiz, int x); 

devolve a raiz da árvore com o elemento removido

*/

no * ArvoreRemove (no * raiz, int x){
  no * y; 
  if (raiz == NULL)
    return NULL;
  if (x < raiz->info)
    raiz->esq = ArvoreRemove(raiz->esq, x);
  else if (x > raiz->info)
    raiz->dir = ArvoreRemove(raiz->dir, x);
  else{
    if (raiz->esq == NULL && raiz->dir == NULL){
      free(raiz);
      raiz = NULL;
    }
    else if (raiz->esq == NULL){
      y = raiz->dir;
      free(raiz);
      raiz = y;
    }
    else if (raiz->dir == NULL){
      y = raiz->esq;
      free(raiz);
      raiz = y;
    }
    else{ /* tem dois filhos */
      y = maximo (raiz->esq);
      raiz->info = y->info;
      raiz->esq = ArvoreRemove (raiz->esq, y->info);
    }
  }
  return raiz;
}

