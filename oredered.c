#include <stdio.h>
#include <omp.h>

int main(void)
{
	unsigned int i = 0, tid = 0;
	#pragma omp parallel for ordered private(tid)
	for(i=0; i<8; ++i) {
		tid = omp_get_thread_num();
		printf("Unordered %d %d\n", tid, i);
		#pragma omp ordered
		{
		printf("Ordered %d %d\n", tid, i);
		}
	}

	return 0;
}