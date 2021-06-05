/* Primos, MDC, MMC e companhia limitada
 * Precisa ser adequado ao resto das libs.
 * 
 * */

char eh_primo(unsigned int n){
	if (n<=1){return 0;}
	int i;
	for (i=2;i<n;i++){
		if(n%i==0) return 0;
		if(i*i > n) break;
	}
	return 1;
}

char eh_primo_fast(unsigned int n,dyn_unsint* list){
	/*
	Determina se list contém um fator de n.
	*/
	while(list!=NULL){
		if(n % list->value == 0) return 0;
		if(list->value*list->value > n) break;
		list = list->next;
	}
	return 1;
}

dyn_unsint* lista_de_primos(unsigned int n){
	/*
	Retorna o vetor com uma lista de primos
	estritamente menores do que n.
	*/
	if(n<=2) return NULL;

	dyn_unsint* list;
	int i;

	list = create_dyn_unsint(2);
	for(i=3;i<n;i++){
		if(eh_primo(i)){
			append_dyn_unsint(list,i);
		}
	}

	return list;
}

dyn_unsint* lista_de_primos_fast(unsigned int n){
	/*
	Retorna o vetor com uma lista de primos
	estritamente menores do que n.
	*/
	if(n<=2) return NULL;

	dyn_unsint* list;
	int i;

	list = create_dyn_unsint(2);
	for(i=3;i<n;i++){
		if(eh_primo_fast(i,list)){
			append_dyn_unsint(list,i);
		}
	}

	return list;
}

int problema2_fast(int n){
	int i,j,length,matches;
	unsigned int* v;
	dyn_unsint* list;

	// printf("Digite n: ");
	// scanf("%d", &n);

	list = lista_de_primos_fast(n);
	// print_dyn_unsint(list);
	length = length_dyn_unsint(list);
	v = vector_dyn_unsint(list);
	del_dyn_unsint(list);

	matches = 0;

	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			if(v[i]+v[j]==n){
				printf("%d + %d = %d\n",v[i],v[j],n);
				if(i==j) matches += 2;
				else matches++;
			}
		}
	}
	matches = matches/2;
	printf("Há %d pares que satisfazem o caso",matches);
	return matches;

}

int problema2(int n){
	/*Veja: Conjectura de Goldbach*/
	int i,j,length,matches;
	dyn_unsint *list, *list2, *start_ptr;

	// printf("Digite n: ");
	// scanf("%d", &n);

	list = lista_de_primos_fast(n);
	list2 = list;
	start_ptr = list;

	matches = 0;

	while(list!=NULL){
		list2 = start_ptr;
		while(list2!=NULL){
			if(list->value+list2->value==n){
				printf("%d + %d = %d\n",
					   list->value,list2->value,n);
				if(list==list2) matches += 2;
				else matches++;
			}
			list2 = list2->next;
		}
		list = list->next;
	}
	matches = matches / 2;
	printf("Há %d pares que satisfazem o caso",matches);
	del_dyn_unsint(list);
	return matches;

}

 /* MDC e MMC */

 int mdc(const int a, const int b){
  int r;
  int m = a, n = b;
  r = m % n;
	while(r != 0){
		m = n;
		n = r;
		r = m % n;
  }
  return n;
 }
 