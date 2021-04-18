#include "omp.h"
#include <stdio.h>
#include <math.h>

double f(a)
double a;
{
    return (4.0 / (1.0 + a*a));
}

int main(int argc, char *argv[]) {
    int  n, i;
    int tid, nthreads;
    double PI25DT = 3.141592653589793238462643;
    double pi, h, sum, x;
    omp_set_num_threads(50);

        n = 100;
        h   = 1.0 / (double) n;
        sum = 0.0;
#pragma omp parallel for reduction(+:pi) private(x, i, tid) 
        for (i = 1; i <= n; i ++) {
            nthreads = omp_get_num_threads();
            tid = omp_get_thread_num();
            printf("El hilo %d, de %d hilos, calcula la iteracion i = %d\n", tid, nthreads, i);
            x = h * ((double)i - 0.5);
            pi += f(x);
        }
        pi = h * pi;
	printf("\nPI = %.16f\n", pi);
}

            
