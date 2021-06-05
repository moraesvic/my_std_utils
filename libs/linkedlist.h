#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef int item;

typedef struct cel {
  item info;
  struct cel * prox;
} celula; 

celula * busca (celula * inicio, item x);

celula * buscaIterativa (celula * inicio, item x);

void insereNoInicio (celula **inicio, item x);

celula * insereNoInicioJeito2 (celula *inicio, item x);

celula * insereNoFim (celula * inicio, item x);

celula * insereNoFimRec (celula * inicio, item x);

celula * insereOrdenado (celula * inicio, item x);

celula * insereOrdenadoIter (celula * inicio, item x);

celula * removePrimeiro (celula * inicio);

celula * LLremove (celula * inicio, item x);

celula * removeIter (celula * inicio, item x);

#endif /* LINKEDLIST_H */
