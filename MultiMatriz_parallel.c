#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 2000
#define CHUNK 100

void imprimir(int size, double **Matriz)
{
   printf("\n");
   int i, j;

    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            printf("%.2f\t", Matriz[i][j]);
        }
        printf("\n");
    }
}

void multimatriz(int size, double **MatrizA, double **MatrizB, double **MatrizC)
{
	int i, j, k, chunk;
	double soma;

	chunk=CHUNK;

#pragma omp parallel shared(MatrizA, MatrizB, MatrizC, size, chunk) private(i, j, k, soma)
{
	for(i=0;i<size;i++)
	{
		#pragma omp for
		for(j=0;j<size;j++)
		{
			soma=0;

			for(k=0;k<size;k++)
			{
				soma += MatrizA[i][k]*MatrizB[k][j];
			}

			MatrizC[i][j] = soma;
			soma=0;
		}
	}
}
#pragma omp barrier
	printf("Matriz C\n");
   imprimir(N, MatrizC);
   printf("\n");

}

int main()
{
	int i, j, k;
	static double **MatrizA, **MatrizB, **MatrizC;
   double soma=0;

	MatrizA = (double**)malloc(N * sizeof(double*));
	MatrizB = (double**)malloc(N * sizeof(double*));
	MatrizC = (double**)malloc(N * sizeof(double*));

   for(i=0;i<N;i++)
   {
		MatrizA[i] = (double*)malloc(N * sizeof(double*));
		MatrizB[i] = (double*)malloc(N * sizeof(double*));
		MatrizC[i] = (double*)malloc(N * sizeof(double*));
   }

	 for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            MatrizA[i][j] = (double) rand()/RAND_MAX;
       		MatrizB[i][j] = (double) rand()/RAND_MAX;
			}

    }

	/*printf("Matriz A\n");
   imprimir(N, MatrizA);
   printf("\n");

	printf("Matriz B\n");
   imprimir(N, MatrizB);
   printf("\n");*/

	printf("Multiplicando as Matrizes \n");
	multimatriz(N, MatrizA, MatrizB, MatrizC);

 return 0;
}
