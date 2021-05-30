#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> // time()

#define L 5
#define SEED (time(NULL)) // random seed

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

	double start = 0.0;
	double elapsed = 0.0;
	start = omp_get_wtime();

	int M=0; //Magentizacion

	#pragma omp parallel num_threads(4)  reduction(+:M)
	{
		for (i=0; i<L; i++){
			for (j=0; j<L; j++){
				float p = rand()/(float)RAND_MAX;			
				matrix[idx(i,j)] = (p<0.5) ? -1:1;
			}
		}
		#pragma omp barrier
		//if (L < 10) print_matrix(matrix);
		
		for (i = 0; i < L; ++i){
			for ( j = 0; j < L; ++j){
				M += matrix[idx(i,j)];
			}
		}
		printf("Magent: %2i %2i \n", M, omp_get_thread_num());
	}

	printf("\n");
	elapsed = omp_get_wtime()-start;
	printf("Magent: %i \n", M );
	printf("Tiempo: %f \n", elapsed );



	free(matrix);
	return 0;
}