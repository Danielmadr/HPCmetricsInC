#ifndef PERFORMANCE_UTILS_H
#define PERFORMANCE_UTILS_H

#include <time.h>

// Função para medir o tempo de execução de um trecho de código
double measure_time_generic(void (*multiply_func)(double **, double **, double **, int, void *),
                            double **A, double **B, double **C, int N, void *extra_data);

double measure_time_no_blocking(void (*multiply_func)(double **, double **, double **, int),
                                double **A, double **B, double **C, int N);

double measure_time_with_blocking(void (*multiply_func)(double **, double **, double **, int, void *),
                                  double **A, double **B, double **C, int N, int block_size);

#endif // PERFORMANCE_UTILS_H