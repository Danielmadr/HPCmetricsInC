#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_utils.h"

// Implementação da função genérica
double measure_time_generic(void (*multiply_func)(double **, double **, double **, int, void *),
                            double **A, double **B, double **C, int N, void *extra_data)
{
  if (!A || !B || !C || !multiply_func || N <= 0)
  {
    fprintf(stderr, "Invalid input to measure_time function.\n");
    return -1.0;
  }

  reset_matrix(C, N);
  // printf("_____________________________\ncomeço\n");
  // print_matrix(C, N); // Somente se necessário

  clock_t start, end;
  start = clock();
  multiply_func(A, B, C, N, extra_data);
  end = clock();

  // printf("fim\n");
  // print_matrix(A, N); // Somente se necessário
  // print_matrix(B, N); // Somente se necessário
  // print_matrix(C, N); // Somente se necessário
  // printf("____________________________fim\n");

  return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Para funções sem blocagem e sem extra_data
double measure_time_no_blocking(void (*multiply_func)(double **, double **, double **, int),
                                double **A, double **B, double **C, int N) {
    return measure_time_generic((void (*)(double **, double **, double **, int, void *))multiply_func, A, B, C, N, NULL);
}

// Para funções com blocagem e com extra_data
double measure_time_with_blocking(void (*multiply_func)(double **, double **, double **, int, void *),
                                   double **A, double **B, double **C, int N, int block_size) {
    // printf("block_size: %d\n", block_size);
    return measure_time_generic(multiply_func, A, B, C, N, (void *)&block_size);
}