#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>

#define LENUM_BUFFER_SIZE 32
#define LEPALAVRA_BUFFER_SIZE 32

#define LINHA_SEPARADORA "--------------------------------------------------\n"

void inverteString(char *str, int n);

int ehMinuscula(char c);

int ehMaiuscula(char c);

int strMenorIgualQue(char *p, char *q);

int strComp(char *p, char *q);

int strLen(char * s);

void zerarStr(char * s, int len);

char * newStr(char * s);

int my_pow10(int p);

int my_atoi(char * s);

void strCopy(char *a, char *b);

void strAppend(char *a, char *b);

int leNum(char * input, int * pos);

int validNum(char c);

#endif