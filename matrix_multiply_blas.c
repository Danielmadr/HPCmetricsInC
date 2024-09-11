#include "matrix_utils.h"
#include "matrix_multiply_blas.h"
#include <cblas.h>
#include <stdlib.h>

// CBLAS Implementation of Matrix Multiplication
void matrix_multiply_cblas(double **A, double **B, double **C, int N)
{
    // Flatten the matrices
    double *a_flat = (double *)malloc(N * N * sizeof(double));
    double *b_flat = (double *)malloc(N * N * sizeof(double));
    double *c_flat = (double *)malloc(N * N * sizeof(double));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a_flat[i * N + j] = A[i][j];
            b_flat[i * N + j] = B[i][j];
            c_flat[i * N + j] = 0;
        }
    }

    // Perform the matrix multiplication
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, a_flat, N, b_flat, N, 0.0, c_flat, N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = c_flat[i * N + j];
        }
    }

    free(a_flat);
    free(b_flat);
    free(c_flat);
}
