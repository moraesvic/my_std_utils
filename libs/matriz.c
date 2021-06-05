#include "matriz.h"

int ** alocaMatriz(int lin, int col){
	int i;
	int ** mat = calloc(lin, sizeof(int*));
	for(i=0;i<lin;i++) mat[i] = calloc(col,sizeof(int));
	return mat;
}

void liberaMatriz(void ** mat, int lin){
	int i;
	if(mat!=NULL){
		for(i=0;i<lin;i++) free(mat[i]);
		free(mat);
	}
}

int ** cpMatriz(int ** mat, int lin, int col){
	int i, j, **newMat = alocaMatriz(lin,col);
	for(i=0;i<lin;i++)
		for(j=0;j<col;j++)
			newMat[i][j] = mat[i][j];
	return newMat;
}

void printMatriz(int ** mat, int lin, int col){
	int i, j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++)
			printf("%3d", mat[i][j]);
		printf("\n");
	}
}

void printMatrizChar(int ** mat, int lin, int col){
	int i, j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++)
			if(mat[i][j] == 0)       printf(".");
            else if(mat[i][j] == -1) printf("#");
			else                     printf("%c",mat[i][j]);
		printf("\n");
	}
}