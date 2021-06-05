#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *v;
	int topo;
	int max;
} Pilha;

Pilha * criaPilha();

void destroiPilha(Pilha * p);

void empilha(Pilha * p, int s);

void printPilha(Pilha * p);

int desempilha(Pilha * p);

int topoDaPilha(Pilha * p);

int pilhaVazia(Pilha * p);

void copyVetor(int * v1, int * v2, int size);

#endif