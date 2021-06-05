#include "fileio.h"

FILE *abreArq(char * nomeArq){
/* Dada uma string fileName, tenta abrir o arquivo correspondente. Em caso de
sucesso, retorna o ponteiro para tal arquivo. Em caso de falha, printa mensagem
de erro.
*/
  FILE * arq;
  arq = fopen(nomeArq,"r");
  if (arq == NULL)
    printf ("Não encontrei o arquivo %s\n", nomeArq);
  return arq;
}

int pegaTamArq(char * nomeArq){
/* Dada uma string nomeArq que contém o nome do arquivo, retorna o tamanho
desse arquivo em bytes.

A função poderia ser implementada com as funções fseek e ftell do <stdio.h>,
conforme descrito  no link abaixo, mas preferimos usar o
procedimento descrito no enunciado no EP1 para ser mais transparente quanto
ao funcionamento do programa.

https://www.geeksforgeeks.org/c-program-find-size-file/

No momento ainda não vamos ler de fato o arquivo, isso ficará para a função
leArq. Isso para que tenhamos um controle preciso da memória. Mas, para poder
usar fscanf, vamos precisar empregar uma variável dummy ("tapa buraco").
*/
  int tam = 0;
  char tapaBuraco;
  FILE * arq = abreArq(nomeArq);
  while (!feof(arq))
  {
    fscanf(arq,"%c",&tapaBuraco);
    tam++;
  }
  fclose(arq);
  printf("\nLi %d byte(s) em \"%s\":\n", --tam, nomeArq);
  return tam;
}

char * leArq(char * nomeArq){
/* Define, por meio de pegaTamArq, quanta memória deve ser alocada
para o input.

A esse tamanho, vamos acrescentar um byte, para o caractere terminal \0.
Aloca tal memória com calloc e lê o conteúdo do arquivo para uma
string (vetor de chars). Retorna um ponteiro para o vetor alocado.
*/
  int tam = pegaTamArq(nomeArq);
  int i = 0;
  char * texto = calloc(tam + 1, sizeof(char));
  if (texto == NULL) printf("calloc retornou NULL!\n");
  FILE * arq = abreArq(nomeArq);
  while (!feof(arq))
  {
    fscanf(arq,"%c",texto + i);
    i++;
  }
  fclose(arq);
  /*
  Não precisamos fazer texto[tam] = 0, uma vez que todos os valores do
  vetor já foram inicializados com 0 por calloc.
  */
  return texto;
}