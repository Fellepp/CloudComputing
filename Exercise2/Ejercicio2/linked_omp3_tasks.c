#include <omp.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 40
#endif

struct node {
  int data;           // An integer (the data to be computed)
  int fibdata;        // The result of fib(data)
  int thid;           // Thread id of the thread that computes the node
  struct node* next;
};

struct node* init_list(struct node* p);
void process(struct node* p); 
int fib(int n); 


// Computes the n-th term of the Fibonacci sequence
int fib(int n) {
  if (n < 2) 
    return (n);
  else 
    return (fib(n - 1) + fib(n - 2));
}

// Process a linked list node 
// Computes the corresponding Fibonacci number
void process(struct node* p) {
  int n, temp;
  n = p->data;
  temp = fib(n);

  p->fibdata = temp;
}

struct node* init_list(struct node* p) {
  int i;
  struct node* head = NULL;
  struct node* temp = NULL;
  
  head = malloc(sizeof(struct node));
  p = head;
  p->data = FS;
  p->fibdata = 0;
  for (i = 0; i < N; i++) {
    temp = malloc(sizeof(struct node));
    p->next = temp;
    p = temp;
    p->data = FS + i + 1;
    p->fibdata = i + 1;
  }
  p->next = NULL;
  return head;
}

int main() {
  double start, end;
  struct node *e = NULL;
  struct node *temp = NULL;
  struct node *head = NULL;

  printf("Process linked list\n");
  printf(" Each linked list node will be processed by function 'process()'\n");
  printf(" Each ll node will compute %d fibonacci numbers beginning with %d\n", N, FS);   

  e = init_list(e);
  head = e;

  start = omp_get_wtime();
  #pragma omp parallel 
  {
    #pragma omp master
       printf("Threads:   %d\n", omp_get_num_threads());
    #pragma omp single
    {
      for (e = head; e; e = e->next) {
        #pragma omp task firstprivate(e) //first private is required
          process(e);
      }
    }
  }
  end = omp_get_wtime();
  e = head;
  while (e != NULL) {
    printf("%d : %d\n", e->data, e->fibdata);
    temp = e->next;
    free (e);
    e = temp;
  } 
  free (e);
  printf("Compute Time: %f seconds\n", end - start);
  return 0;
}

