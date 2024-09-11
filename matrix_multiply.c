#include "matrix_utils.h"

// ijk implementation
void matrix_multiply_ijk(double **A, double **B, double **C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// ikj implementation
void matrix_multiply_ikj(double **A, double **B, double **C, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int j = 0; j < N; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// jik implementation
void matrix_multiply_jik(double **A, double **B, double **C, int N)
{
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < N; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// jki implementation
void matrix_multiply_jki(double **A, double **B, double **C, int N)
{
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int i = 0; i < N; i++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// kij implementation
void matrix_multiply_kij(double **A, double **B, double **C, int N)
{
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// kji implementation
void matrix_multiply_kji(double **A, double **B, double **C, int N)
{
    for (int k = 0; k < N; k++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
