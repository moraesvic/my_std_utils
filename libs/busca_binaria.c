
int busca_bin(int *v, int ini, int fim, int elem){
  /*
   * busca_bin(v, 0, n_elem, elem)
   * Recebe um vetor ordenado v, e encontra o índice de elem
   * dentro dele, ou retorna -1 caso não exista.
   * 
   * O índice fim nunca é acessado. Isso é garantido pelo
   * critério de parada. meio só seria == fim se ini == fim.
   * 
   * Analogia: é como procurar uma palavra num dicionário.
   * Abre o dicionário no meio. Está mais adiante ou mais
   * atrás? Selecione a partição adequada e repita a operação.
   *
   * Análise: a complexidade é log(n). O pior caso é o que
   * o elemento buscado está em uma extremidade do vetor.
   * Então a função terá de ser chamada
   * math.ceil(log2(n)) vezes.
   */
  int meio;

  if(ini == fim) return -1;
  meio = (ini + fim)/2;
  if(v[meio] == elem) return meio;
  return v[meio] < elem ? busca_bin(v, ini,    meio, elem)
                        : busca_bin(v, meio+1, fim,  elem);
}