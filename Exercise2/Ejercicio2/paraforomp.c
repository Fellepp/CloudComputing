// OMP -- paraforomp.c

#include <stdio.h>
#include <omp.h>
#define N    4
#define M    4

int main () {

    int i, j;
    int nthreads, tid;
    int n, m, sum;
    int a[M], c[N] = {1, 1, 1, 1}, b[M][N] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    // Algunas inicializaciones
    n = m = 4;
    // Las variables a, b, c, m, n, nthreads son de tipo compartido
    // Las variables i, j, sum, tid son de tipo privado
#pragma omp parallel for default(none) \
	private(tid, i, j, sum) shared(m, n, a, b, c, nthreads)
    for (i = 0; i < m; i++) {
        tid = omp_get_thread_num();       
        nthreads = omp_get_num_threads();	
        sum = 0;
        for (j = 0; j < n; j++)
            sum += b[i][j] * c[j];
	a[i] = sum;
	printf("El hilo %d, de %d hilos, calcula la iteracion i = %d\n", tid, nthreads, i);
	
    }
    for (i = 0; i < m; i++)
	printf("a[%d] = %d\n", i, a[i]); 
}

