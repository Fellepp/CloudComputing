// OMP -- sectionomp.c

#include <stdio.h>
#include <omp.h>

int main () {

    int i;
    int nthreads, tid;
    // La variable tid es privada a cada hilo
#pragma omp parallel private(tid)
{
    #pragma omp sections
    {
       #pragma omp section 
       {
          tid = omp_get_thread_num();
	  nthreads = omp_get_num_threads();
          printf("El hilo %d, de %d, calcula la seccion 1\n", tid, nthreads);
       }
       #pragma omp section
       {
          tid = omp_get_thread_num();
          nthreads = omp_get_num_threads();
          printf("El hilo %d, de %d, calcula la seccion 2\n", tid, nthreads);
       }
       #pragma omp section
       {
          tid = omp_get_thread_num();
          nthreads = omp_get_num_threads();
          printf("El hilo %d, de %d, calcula la seccion 3\n", tid, nthreads);
       }
       #pragma omp section
       {
          tid = omp_get_thread_num();
          nthreads = omp_get_num_threads();
          printf("El hilo %d, de %d, calcula la seccion 4\n", tid, nthreads);
       }
		     
       
    }  // fin de las sections
}  // fin de la parallel section 




}

