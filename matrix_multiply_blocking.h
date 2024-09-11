#ifndef MATRIX_MULTIPLY_BLOCKING_H
#define MATRIX_MULTIPLY_BLOCKING_H

void matrix_multiply_blocking(double **A, double **B, double **C, int N, void *block_size_ptr, void *loop_order);

#endif
