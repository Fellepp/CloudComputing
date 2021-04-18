// OMP -- foromp.c
#include <stdio.h>
#include <omp.h>
#define CHUNKSIZE 2 
#define N    10

int main () {

    int i, chunk;
    int nthreads, tid;
    
    int a[N], b[N], c[N];
    // Algunas inicializaciones
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;
    // Las variables a, b, c, chunk son de tipo compartido
    // Las variables i, tid son privadas a cada hilo
#pragma omp parallel shared(a, b, c, chunk) private(i, tid)
{
    // Se realiza una asignacion estatica de iteraciones 
    // en la que el tamaÃo del bloque se fija a chunk
    #pragma omp for schedule(static, chunk) 
    for (i = 0; i < N; i++) {
        tid = omp_get_thread_num();       
        nthreads = omp_get_num_threads();	
        c[i] = a[i] + b[i];
	printf("El hilo %d, de %d hilos, calcula la iteracion i = %d\n", tid, nthreads, i);
		
    }
}  // Fin de la region paralela

}

