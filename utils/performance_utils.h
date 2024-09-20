#ifndef PERFORMANCE_UTILS_H
#define PERFORMANCE_UTILS_H

#include <time.h>

void avaliar_funcao_com_block(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, int block_size, char *loop_order, long long *resultados, double *time, char *method);

void avaliar_funcao_sem_block(void (*multiply_func)(double **, double **, double **, int), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados, double *time, char *method);

#endif // PERFORMANCE_UTILS_H