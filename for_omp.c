#include <stdio.h>
#include <omp.h>

#define N 8192

float a[N];

int main(void)
{
	unsigned int i = 0;
	#pragma omp parallel
	{
		#pragma omp for
		for(i=0; i<N; ++i) {
			a[i] *= a[i];
		}
	}

	return 0;
}