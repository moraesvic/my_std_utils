#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

int ** alocaMatriz(int lin, int col);

void liberaMatriz(void ** mat, int lin);

void printMatriz(int ** mat, int lin, int col);

void printMatrizChar(int ** mat, int lin, int col);

#endif