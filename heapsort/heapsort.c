#include <stdio.h>
#include <stdlib.h>
#include "../libs/my_random.h"
#include "../libs/my_string.h"
#include "heapsort.h"

#define MAX_SIGNED_INT 0x7fffffff
#define MAX_RANGE 100
#define MAX_IT 1
#define PRINT 1
#define PRINT_BIN 0

#define INT_FORMAT "%c%c%c%c"
#define INT_PRINT(x) (x), (x >> 8), (x >> 16), (x >> 24)

void swap(int *x, int *y){
  int temp = *x;
  *x = *y;
  *y = temp;
}

void sobe(int *v, int k){
  /* aplicando o bottom-up reheapify ("swim") conforme descrito
   * no livro Algorithms .
   *
   * Vamos receber um heap e o índice de um de seus elementos, 
   * e subi-lo para a posição correta. Essa função é apropriada
   * para colocar um elemento recém-adicionado na sua posição correta.
   *
   * Falamos "subir" porque a árvore é vista de ponta-cabeça.
   * Em outras palavras, o elemento será movido em direção à raiz,
   * mas nas árvores da vida real, a raiz é o ponto mais baixo da árvore.
   * 
   * Isso pode causar alguma confusão. */

  while(k > 0 && v[(k-1)/2] < v[k])
  {
    swap(v + k, v + k/2);
    k = k/2;
  }
}

void insere_e_sobe(int *v, int pos, int novo){
  v[pos] = novo;
  sobe(v, pos);
}

void desce(int *v, int pai, int final){
  /* Esse é o algoritmo "sink" descrito no livro Algorithms.
   *
   * Ele recebe um int pai, e um int final, tal que
   * 0 <= pai < final , e desce o elemento pai em direção
   * às folhas.
   *
   * Esse algoritmo é o ideal para heapificar um heap totalmente fora de ordem.
   * */
  int filho;
  while(2*pai < final)
  {
    filho = 2*pai;
    /* verifica qual é o maior irmão, se é que há um irmão */
    if(filho + 1 < final && v[filho] < v[filho+1]) filho++;
    /* se o pai é maior que o maior filho, nada a fazer */
    if(v[pai] >= v[filho]) break;
    /* troca o pai pelo maior filho e reaplica o algoritmo,
     * colocando os filhos do novo filho em seus lugares */
    swap(v + pai, v + filho);
    pai = filho;
  }
}

void desce_geral(int *v, int n){
  /* Essa é a função que na aula de 27/10 de MAC-0121
   * foi chamada heapifica.
   *
   * Não é necessário descer praticamente metade do vetor,
   * já que esses elementos correspondem às folhas e sua
   * subárvore já está heapificada.
   *
   * Veja também a ilustração de Lucas Medina no E-Disciplinas.
   */
  int i;
  for(i = (n-2)/2; i >= 0; i--)
    desce(v, i, n);
}

void print_vetor(int *v, int len){
  int i;
  for(i = 0; i < len; i++)
    printf("%d ", v[i]);
  printf("\n");
}

void print_vetor_bin(int *v, int len){
  int i;
  for(i = 0; i < len; i++)
    printf(INT_FORMAT, INT_PRINT(v[i]));
}

void sortdown(int *v, int n){
    /* a cada iteração, tirar o maior elemento da posição 0
       e movê-lo para a posição final (definida como
       topo - 1 - descidas). Pegar o elemento dessa posição
       e colocá-lo no começo. Descê-lo (desce), limitando
       o heap às primeiras posições.
    */
  int descidas;
  for(descidas = 0; descidas < n; ++descidas)
  {   
      swap(v, v + n - 1 - descidas);
      desce(v, 0, n - 1 - descidas);
  }
}

void heapsort_vetor(int *v, int n){
  /* Por meio da estrutura auxiliar "heap", ordena um vetor
   * recebido. 
   * Quando a gente chega nessa altura do campeonato, percebe
   * que nem precisava ter implementado o struct Heap, dava
   * para fazer tudo com o vetor in-place sem maiores problemas. */
  if(n == 0)
    return;  
  desce_geral(v, n);
  if(PRINT) print_vetor(v, n);
  sortdown(v, n);
}

void segmento_1(int *v, int n){
  /* TESTE 1 */
  int i;
  if(PRINT)
      printf("\nTESTE 1: insere elementos no heap, "
             "sobe cada um conforme é inserido\n\n");
  for(i = 0; i < n; i++)
    insere_e_sobe(v, i, my_randint_mod(MAX_RANGE));
  if(PRINT) print_vetor(v, n);
}

void segmento_2(int *v, int n){
  /* TESTE 2 */
  int i;
  if(PRINT)
      printf("\nTESTE 2: insere os elementos, "
             "depois desce-os a partir do fim\n\n");
  for(i = 0; i < n; i++)
    v[i] = my_randint_mod(MAX_RANGE);
  desce_geral(v, n);
  if(PRINT) print_vetor(v, n);
}

void segmento_3(int *v, int n){
  /* TESTE 3 */
  int i;
  if(PRINT)
      printf("\nTESTE 3: dado um vetor, aplica heapsort\n\n");
  for(i = 0; i < n; i++)
    v[i] = my_randint_mod(MAX_RANGE);
  if(PRINT) print_vetor(v, n);
  heapsort_vetor(v, n);
  if(PRINT) print_vetor(v, n);
  if(PRINT_BIN) print_vetor_bin(v, n);
}

int main(int argc, char *argv[]){
  if(argc != 2)
  {
    printf("Erro: Digite o tamanho do vetor de inteiros\n");
    return 0;
  }
  const unsigned max_elementos = my_atoi(argv[1]);
  int i, *v;
  v = calloc(max_elementos, sizeof(int));
  for(i = 0; i < MAX_IT; i++)
  {
      segmento_1(v, max_elementos);
      segmento_2(v, max_elementos);
      segmento_3(v, max_elementos);
  }
  return 0;
  /* */

}
