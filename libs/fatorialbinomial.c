#include <stdlib.h>


unsigned long fatorial(int n){
	if(n<=1) return 1;
	else return n*fatorial(n-1);
}

void reflete_lista(unsigned long *v, int n){
	int i;

	if(n>0 && n%2) v[n/2+1] = v[n/2];
	for(i=1;i<=n/2;i++) v[n/2+i+n%2] = v[n/2-i];
}

unsigned long *binomial1(int n){
	/* Aguenta até n=20 */
	int i;
	unsigned long *v = malloc(sizeof(unsigned long)*(n+1));
	for(i=0;i<=n;i++){
		v[i] = fatorial(n)/fatorial(i)/fatorial(n-i);
	}
	return v;
}

unsigned long *binomial2(int n){
	/* Aguenta até n=20. Aproveita-se da simetria
	da árvore de Pascal e portanto leva cerca de
	metade do tempo da anterior */
	int i;
	unsigned long *v = malloc(sizeof(unsigned long)*(n+1));
	for(i=0;i<=n/2;i++){
		v[i] = fatorial(n)/fatorial(i)/fatorial(n-i);
	}
	reflete_lista(v,n);
	return v;
}

unsigned long *binomial3(int n){
	/* Aguenta até n=29. Economiza no cálculo de
	fatoriais, cortando divisões desnecessárias.
	Vale-se também da simetria. */
	int i,j;
	unsigned long *v = malloc(sizeof(unsigned long)*(n+1));
	for(i=0;i<=n/2;i++){
		v[i] = 1;
		for(j=n-i+1;j<=n;j++) v[i] *= j;
		v[i] /= fatorial(i);
	}
	reflete_lista(v,n);
	return v;
}

unsigned long* binomial4(int n){
	/* Aguenta até n=32. Em vez de calcular o fatorial,
	simplesmente constrói a árvore e pega os números.
	*/
	int i;
	unsigned long *v;
	v = malloc(sizeof(unsigned long)*(n+1));
	v[0] = 1;
	if(n==0) return v;

	unsigned long *prev_list;
	v[n] = 1;
	prev_list = binomial4(n-1);

	/* O código aplicado abaixo tem custo muito baixo e
	vale mais a pena do que a reflexão da lista, que no
	fim das contas também envolve uma série de somas e
	divisões.
	*/

	for(i=1;i<n;i++) v[i] = prev_list[i-1]+prev_list[i];
	
	free(prev_list);
	return v;
}