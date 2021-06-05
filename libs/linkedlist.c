#include "linkedlist.h"

/*

Faça uma função 

void imprimeLista (celula *inicio);

*/ 


void imprimeLista (celula * inicio) {
  if (inicio != NULL) {
    printf ("%d ", inicio->info);
    imprimeLista (inicio->prox);
  }
  else printf("\n"); 
}

void imprimeListaIterativo (celula * inicio) {
  celula * p;
  for (p = inicio; p != NULL; p = p -> prox)
    printf("%d ", p->info); 
  printf("\n");
} 


/* 

celula * busca (celula *inicio, item x);

*/

celula * busca (celula * inicio, item x) {
  if (inicio == NULL || inicio -> info == x)
    return inicio;
  return (busca (inicio->prox, x));
}

celula * buscaIterativa (celula * inicio, item x) {
  celula * p;
  for (p = inicio; p != NULL && p->info != x; p = p->prox);
  return p;
}



/* 

void insereNoInicio (celula **inicio, item x);

*/

void insereNoInicio (celula **inicio, item x) {
  celula * novo = malloc (sizeof(celula)); 
  novo->info = x;
  novo->prox = *inicio;
  *inicio = novo; 
}

/* na chamada da função, 

celula * inicio = NULL; 
... 
insereNoInicio (&inicio, 23); 

*/ 

/* 

celula * insereNoInicio (celula *inicio, item x);

*/

celula * insereNoInicioJeito2 (celula *inicio, item x){
  celula * novo = malloc(sizeof(celula));
  novo->info = x;
  novo->prox = inicio;
  return (novo);
}

/* na chamada da função 

celula * inicio; 
... 
inicio = insereNoInicioJeito2 (inicio, 23); 

*/

/* 

Insere no fim da lista

*/

celula * insereNoFim (celula * inicio, item x) {
  celula *novo = malloc(sizeof (celula));
  celula *atual, *ant; 
  novo->info = x;
  novo->prox = NULL; 
  for (atual = inicio, ant = NULL; atual != NULL;
       ant = atual, atual = atual->prox);
  if (ant != NULL)
    ant -> prox = novo;
  else
    inicio = novo;
  return (inicio);
}


celula * insereNoFimRec (celula * inicio, item x) {
  if (inicio == NULL) {
    inicio = malloc (sizeof(celula));
    inicio->info = x;
    inicio->prox = NULL;
  } 
  else inicio->prox = insereNoFimRec (inicio->prox, x);
  
  return inicio;
} 
  
/* 

celula * insereOrdenado (celula *inicio, item x); 

*/

celula * insereOrdenado (celula * inicio, item x) {
  celula * aux; 
  if (inicio == NULL || inicio->info >= x) {
    aux = inicio; 
    inicio = malloc(sizeof(celula));
    inicio->info = x;
    inicio->prox = aux;
  }
  else inicio->prox = insereOrdenado (inicio->prox, x);
  return inicio;
}

celula * insereOrdenadoIter (celula * inicio, item x) {
  celula *atual, *ant, *novo;
  for (ant = NULL, atual = inicio; atual != NULL && atual->info < x;
       ant = atual, atual = atual ->prox);
  novo = malloc(sizeof(celula));
  novo->info = x;
  novo->prox = atual;
  if (ant != NULL)
    ant->prox = novo;
  else
    inicio = novo;
  return inicio;
} 
  
  


 
/* 

celula * removePrimeiro (celula * inicio); 


*/

celula * removePrimeiro (celula * inicio) {
  celula * aux = inicio; 
  if (inicio != NULL){
    inicio = inicio->prox;
    free (aux);
  } 
  return inicio;
} 


/* 

Remove uma ocorrência de x da lista apontada por inicio

celula * remove (celula * inicio, item x); 

*/


celula * LLremove (celula * inicio, item x) {
  celula * aux = inicio; 
  if (inicio == NULL) return inicio;
  if (inicio->info == x){
    inicio = inicio->prox;
    free (aux);
  }
  else  inicio->prox = LLremove(inicio->prox, x); 
  return (inicio);
} 

celula * removeIter (celula * inicio, item x) {
  celula *ant, *atual;
  for (ant = NULL, atual = inicio; atual != NULL && atual->info != x;
       ant = atual, atual = atual->prox);
  if (atual == NULL) return inicio;
  if (ant != NULL)
    ant->prox = atual->prox;
  else
    inicio = atual->prox;
  free (atual);
  return inicio;
} 


/* 

Implementar uma pilha usando listas ligadas: 

topo é um ponteiro para o inicio da lista; 

empilha: insere no início

desempilha: removePrimeiro

pilha está vazia se topo == NULL

*/


/* 

Implementar uma fila usando listas ligadas: exercício!!

Pense em usar dois ponteiros, um para o inicio e outro para o 
fim da fila

*/ 



