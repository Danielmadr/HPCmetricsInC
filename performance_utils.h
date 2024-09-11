#ifndef PERFORMANCE_UTILS_H
#define PERFORMANCE_UTILS_H

#include <time.h>

// Função para medir o tempo de execução de um trecho de código
double measure_time_generic(void (*multiply_func)(double **, double **, double **, int, void *, void *),
                            double **A, double **B, double **C, int N, void *extra_data, void *extra_data2);

double measure_time_no_blocking(void (*multiply_func)(double **, double **, double **, int),
                                double **A, double **B, double **C, int N);

double measure_time_with_blocking(void (*multiply_func)(double **, double **, double **, int, void *, void *),
                                  double **A, double **B, double **C, int N, int block_size, char *loop_order);

void avaliar_funcao_com_block(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, int block_size, char *loop_order, long long *resultados);

void avaliar_funcao_sem_block(void (*multiply_func)(double **, double **, double **, int), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados);

#endif // PERFORMANCE_UTILS_H