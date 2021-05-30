#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> // time()

#define L 6
#define SEED (1622345249) // random seed

int idx(int x, int y){
	return y + x*L;
}

void print_matrix(int matrix[L]){
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			printf("%2d ", matrix[idx(i,j)]);			
		}
		printf("\n");
	}
}

int main(void){

	int i,j;
	long int size = L * L * sizeof(long int);
	int * matrix = malloc(size);

	//rand config
	srand(SEED);
	printf("%d\n", SEED);

	double start = 0.0;
	double elapsed = 0.0;
	start = omp_get_wtime();

	int M=0; //Magentizacion

	#pragma omp parallel
	{
		#pragma omp for collapse(2)
		for (i=0; i<L; i++){
			for (j=0; j<L; j++){
				float p = rand()/(float)RAND_MAX;			
				matrix[idx(i,j)] = (p<0.5) ? -1:1;
				//printf("[%d, %d, %d, %d ] ", i,j, omp_get_thread_num(), matrix[idx(i,j)]);
				printf("[(%i,%i), %d ]",i,j,omp_get_thread_num());
			}
		}
	}//pragma 

	for (i = 0; i < L; ++i){
		for ( j = 0; j < L; ++j){
			M += matrix[idx(i,j)];
			}
	}
	  

	printf("\n Magent: %2i %2i \n", M, omp_get_thread_num());
	printf("\n");
	elapsed = omp_get_wtime()-start;
	printf("Magent: %i \n", M );
	printf("Tiempo: %f \n", elapsed );

	free(matrix);
	return 0;
}