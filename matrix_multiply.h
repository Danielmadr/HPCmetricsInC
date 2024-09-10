#ifndef MATRIX_MULTIPLY_H
#define MATRIX_MULTIPLY_H

void matrix_multiply_ijk(double **A, double **B, double **C, int N);
void matrix_multiply_ikj(double **A, double **B, double **C, int N);
void matrix_multiply_jik(double **A, double **B, double **C, int N);
void matrix_multiply_jki(double **A, double **B, double **C, int N);
void matrix_multiply_kij(double **A, double **B, double **C, int N);
void matrix_multiply_kji(double **A, double **B, double **C, int N);

#endif
