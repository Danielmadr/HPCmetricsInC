#ifndef MATRIX_MULTIPLY_BLOCKING_H
#define MATRIX_MULTIPLY_BLOCKING_H

void matrix_multiply_blocking_ijk(double **A, double **B, double **C, int N, void *block_size_ptr);
void matrix_multiply_blocking_ikj(double **A, double **B, double **C, int N, void *block_size_ptr);
void matrix_multiply_blocking_jik(double **A, double **B, double **C, int N, void *block_size_ptr);
void matrix_multiply_blocking_jki(double **A, double **B, double **C, int N, void *block_size_ptr);
void matrix_multiply_blocking_kij(double **A, double **B, double **C, int N, void *block_size_ptr);
void matrix_multiply_blocking_kji(double **A, double **B, double **C, int N, void *block_size_ptr);

#endif
