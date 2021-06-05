int encontra_em_heap(int *v, int n, int pos_atual, int elem){
  /* Onde 1 <= pos_atual <= n, e o índice precisa
   * ser decrementado para acessar o array.
   *
   * Análise: parece que o caso médio seria de complexidade
   * log n, mas no pior caso pode ser O(n), visitando
   * todos os nós da árvore.
   */
  int ret = -1;
  if(pos_atual < 1) return -1;
  /* Estamos em um max heap, e os filhos serão cada vez
   * menores. Ou seja, se aqui já está menor do que o elem,
   * nem adianta continuar */
  if(v[pos_atual-1] < elem)
  	return -1;
  if(v[pos_atual-1] == elem)
    return pos_atual;
  if(2*pos_atual <= n)
	  ret = encontra_em_heap(v,n,2*pos_atual,elem);
  else
  	/* Se não tem o primeiro filho, não tem o 2º */
  	return -1;
  /* Vamos procurar na 2ª subárvore só se não achamos na 1ª */
  if(ret == -1 && 2*pos_atual + 1 <= n)
  	ret = encontra_em_heap(v,n,2*pos_atual + 1,elem);
  return ret;
}
