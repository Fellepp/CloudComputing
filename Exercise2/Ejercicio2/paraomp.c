// OpenMP -- paraomp.c 

#include <stdio.h>
#include <omp.h>
int main ()  {

    int nthreads, tid;
    printf("Trabajemos con 4 hilos\n");
    omp_set_num_threads(4);
    // Obtiene el numero de hilos en ejecucion
    nthreads = omp_get_num_threads();  
    printf("Numero de hilos en ejecucion = %d\n", nthreads);
	    
#pragma omp parallel private(tid)     // Expande un grupo de hilos. 
              // Cada hilo contiene sus propias copias de variables
{
    tid = omp_get_thread_num();       // Obtiene el identificador del hilo
    printf("Hola desde el hilo = %d\n", tid);
    if (tid == 0) {   // Esta seccion la ejecuta solo el hilo maestro
        nthreads = omp_get_num_threads();
        printf("Numero de hilos = %d\n", nthreads);
    }
}  // Todos los hilos se unen al hilo maestro y finalizan

	
    printf("Trabajemos ahora con 3 hilos\n");

    omp_set_num_threads(3);
    nthreads = omp_get_num_threads();
    printf("Numero de hilos en ejecucion = %d\n", nthreads);
#pragma omp parallel

{
    tid = omp_get_thread_num(); 
    printf("Hola desde el hilo = %d\n", tid);
    if (tid == 0) {
        nthreads = omp_get_num_threads();
        printf("Numero de hilos = %d\n", nthreads);
    }
}  
}
