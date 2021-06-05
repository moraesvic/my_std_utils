#include "pilha_int.h"

Pilha * criaPilha(){
	Pilha * p = malloc(sizeof(Pilha));
	p->v    = malloc(sizeof(int));
	p->topo = 0;
	p->max  = 1;
	return p;
}

void destroiPilha(Pilha * p){
	free(p->v);
	free(p);
}

void empilha(Pilha * p, int s){
	if(p->topo < p->max) p->v[p->topo++] = s;
	else {
		p->max *= 2;
		int * v2 = malloc(sizeof(int)*p->max);
		copyVetor(p->v,v2,p->max/2);
		free(p->v);
		p->v = v2;
		p->v[p->topo++] = s;
	}
}

void printPilha(Pilha * p){
	int i;
	printf("Esta pilha contém %d itens. Sua capacidade máxima é "
		"de %d itens.\n", p->topo, p->max);
	for(i=0;i<p->topo;i++) printf("%d\n", p->v[i]);
}

int desempilha(Pilha * p){
/* Cuidado, não está liberando a memória da string d*/
	if(!pilhaVazia(p)) return p->v[p->topo-- - 1];
	else {
		printf("Erro: a pilha está vazia!\n");
		return -1;
	}
}

void desempilhaTudo(Pilha * p){
	while(!pilhaVazia(p))
		printf("%d\n", desempilha(p));
}

int topoDaPilha(Pilha * p){
	if(!pilhaVazia(p)) return p->v[p->topo-1];
	else {
		printf("Erro: a pilha está vazia!\n");
		return -1;
	}
}

int pilhaVazia(Pilha * p){
	return !p->topo;
}

void copyVetor(int * v1, int * v2, int size){
/*	Copia o vetor v1 para o vetor v2.
	Espera-se que v2 tenha maior capacidade que v1. */
	int i;
	for(i=0;i<size;i++) v2[i] = v1[i];
}