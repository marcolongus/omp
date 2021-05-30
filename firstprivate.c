#include <stdio.h>
#include <omp.h>

#define Q 7 /* discretizaciÃ³n del histograma */
#define N (1<<28) /* largo del vector */

unsigned int a[N] = {1,2,3,4,5}; /* vector de muestras */
unsigned int m[Q] = {0}; /* histograma */
unsigned int mp[Q] = {0}; /* histograma per-thread*/

int main(void)
{
	unsigned int i = 0;
	#pragma omp parallel firstprivate(mp) shared(a,m)
	{
		#pragma omp for
		for(i=0; i<N; ++i)
			mp[a[i]]++;

		// este i es shared!!!! Caos, horror y destruccion
		for(i=0; i<Q; ++i) {
			#pragma omp atomic
			m[i] += mp[i];
		}
	}
	for(i=0; i<Q; ++i)
		printf("m[%d]=%d\n",i,m[i]);

	return 0;
}

// gcc -O1 -fopenmp parallel-reduction-array-manual-race.c && ./a.out