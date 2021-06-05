#include "arvores.h"

// obs verificar se a macro acima efetua duas vezes o valor de x e de y
// ou como é possível corrigir isso

int contaNo(no * raiz){
  return raiz == NULL ? 0 : 1 + contaNo(raiz->esq) + contaNo(raiz->dir);
}

int altura(no * raiz){
  return raiz == NULL ? -1 : 1 + MAX(altura(raiz->esq),altura(raiz->dir));
}
