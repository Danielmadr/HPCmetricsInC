#include "../../utils/matrix_utils.h"
#include <stdio.h>
#include <string.h>

// Matrix Multiplication with Blocking (Loop ijk configuration)
void matrix_multiply_blocking_ijk(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;

    for (int ii = 0; ii < N; ii += block_size)
    {
        for (int jj = 0; jj < N; jj += block_size)
        {
            for (int kk = 0; kk < N; kk += block_size)
            {
                for (int i = ii; i < ii + block_size && i < N; i++)
                {
                    for (int j = jj; j < jj + block_size && j < N; j++)
                    {
                        for (int k = kk; k < kk + block_size && k < N; k++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Matrix Multiplication with Blocking (Loop ikj configuration)
void matrix_multiply_blocking_ikj(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;
    for (int ii = 0; ii < N; ii += block_size)
    {
        for (int kk = 0; kk < N; kk += block_size)
        {
            for (int jj = 0; jj < N; jj += block_size)
            {
                for (int i = ii; i < ii + block_size && i < N; i++)
                {
                    for (int k = kk; k < kk + block_size && k < N; k++)
                    {
                        for (int j = jj; j < jj + block_size && j < N; j++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Matrix Multiplication with Blocking (Loop jik configuration)
void matrix_multiply_blocking_jik(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;
    for (int jj = 0; jj < N; jj += block_size)
    {
        for (int ii = 0; ii < N; ii += block_size)
        {
            for (int kk = 0; kk < N; kk += block_size)
            {
                for (int j = jj; j < jj + block_size && j < N; j++)
                {
                    for (int i = ii; i < ii + block_size && i < N; i++)
                    {
                        for (int k = kk; k < kk + block_size && k < N; k++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Matrix Multiplication with Blocking (Loop jki configuration)
void matrix_multiply_blocking_jki(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;
    for (int jj = 0; jj < N; jj += block_size)
    {
        for (int kk = 0; kk < N; kk += block_size)
        {
            for (int ii = 0; ii < N; ii += block_size)
            {
                for (int j = jj; j < jj + block_size && j < N; j++)
                {
                    for (int k = kk; k < kk + block_size && k < N; k++)
                    {
                        for (int i = ii; i < ii + block_size && i < N; i++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Matrix Multiplication with Blocking (Loop kij configuration)
void matrix_multiply_blocking_kij(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;
    for (int kk = 0; kk < N; kk += block_size)
    {
        for (int ii = 0; ii < N; ii += block_size)
        {
            for (int jj = 0; jj < N; jj += block_size)
            {
                for (int k = kk; k < kk + block_size && k < N; k++)
                {
                    for (int i = ii; i < ii + block_size && i < N; i++)
                    {
                        for (int j = jj; j < jj + block_size && j < N; j++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

// Matrix Multiplication with Blocking (Loop kji configuration)
void matrix_multiply_blocking_kji(double **A, double **B, double **C, int N, void *block_size_ptr)
{
    int block_size = *(int *)block_size_ptr;
    for (int kk = 0; kk < N; kk += block_size)
    {
        for (int jj = 0; jj < N; jj += block_size)
        {
            for (int ii = 0; ii < N; ii += block_size)
            {
                for (int k = kk; k < kk + block_size && k < N; k++)
                {
                    for (int j = jj; j < jj + block_size && j < N; j++)
                    {
                        for (int i = ii; i < ii + block_size && i < N; i++)
                        {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

void matrix_multiply_blocking(double **A, double **B, double **C, int N, void *block_size_ptr, void *loop_order)
{
    if (strcmp(loop_order, "ijk") == 0)
    {
        matrix_multiply_blocking_ijk(A, B, C, N, block_size_ptr);
    }
    else if (strcmp(loop_order, "ikj") == 0)
    {
        matrix_multiply_blocking_ikj(A, B, C, N, block_size_ptr);
    }
    else if (strcmp(loop_order, "jik") == 0)
    {
        matrix_multiply_blocking_jik(A, B, C, N, block_size_ptr);
    }
    else if (strcmp(loop_order, "jki") == 0)
    {
        matrix_multiply_blocking_jki(A, B, C, N, block_size_ptr);
    }
    else if (strcmp(loop_order, "kij") == 0)
    {
        matrix_multiply_blocking_kij(A, B, C, N, block_size_ptr);
    }
    else if (strcmp(loop_order, "kji") == 0)
    {
        matrix_multiply_blocking_kji(A, B, C, N, block_size_ptr);
    }
    else
    {
        printf("Invalid loop order\n");
    }
}