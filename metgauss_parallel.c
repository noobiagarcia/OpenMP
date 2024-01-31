#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

#define NLIN 3200
#define NCOL 3200
#define CHUNK 100
void gauss(int l, int c, double MatrizA[l][c])
{
    int i, j, k, chunk;
    double x[NLIN], soma=0, m;

	 chunk = CHUNK;
#pragma omp parallel shared(MatrizA, l, c, chunk) private(i, j, k, m)
{
			for(j=0; j<c; j++)   //Triangulação da Matriz
			{
				#pragma omp for
				for(i=0; i<l; i++)
	    		{
	        		if(i>j) //Triangulação superior.
	        		{
		            	m = (MatrizA[i][j]/MatrizA[j][j]);
	            		for(k=0; k<c; k++)
			       			 MatrizA[i][k] = MatrizA[i][k]-(m*MatrizA[j][k]);
	        		}
	    		}
			}
}
#pragma omp barrier
	
	x[l] = MatrizA[l][c-1]/MatrizA[l][l]; //Resultado de uma das incognitas.
	for(i=l; i>=0; i--)
    {
		soma=0;
		for(j=i+1; j<c-1; j++)
		{
		     soma = soma + (MatrizA[i][j]*x[j]); //somando os termos isolados do lado direito das incógnitas.
		}
		x[i]=(MatrizA[i][c-1]-soma)/MatrizA[i][i]; //Aplicando a formula do método.
	   //imprimir(NLIN, NCOL, MatrizA);
	}

	printf("\nA Matriz Final é: ");
	 for(i=0; i<l; i++)
    	printf("\nx[%d] = %.5f\n", i+1, x[i]); //Printando os resultados dos x[i]
}
int main()
{
	int i, j, k, chunk;
	static double MatrizA[NLIN][NCOL], x[NLIN];
	double soma=0, m;

	chunk =	CHUNK;
	for(i=0; i<NLIN; i++)
    {
        for(j=0; j<NCOL; j++)
        	MatrizA[i][j] = (double) rand();
    }
    printf("Aplicando o Método\n");
    gauss(NLIN, NCOL, MatrizA);

 return 0;
}
