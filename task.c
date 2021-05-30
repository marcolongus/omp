#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <assert.h>

int fib(int n) {
	int i, j;
	if (n<2)
		return n;
	#pragma omp task shared(i)
	i = fib(n-1);
	#pragma omp task shared(j)
	j = fib(n-2);
	#pragma omp taskwait
	return i + j;
}

int main(int argc, char **argv)
{
	assert(2==argc);
	#pragma omp parallel
	{
	#pragma omp single
	printf("%d\n", fib(atoi(argv[1]))); // Lost Ina Seaof Parentheses
	}
}