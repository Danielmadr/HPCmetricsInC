#include <stdio.h>
#include <stdlib.h>
#include "../../utils/matrix_utils.h"

// funtion to sum two matrices
void add_matrices(double **A, double **B, double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// function to subtract two matrices
void subtract_matrices(double **A, double **B, double **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassen(double **A, double **B, double **C, int n)
{
    // base case - use normal matrix multiplication
    if (n <= 64)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < n; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return;
    }

    int new_size = n / 2;
    double **A11 = allocate_matrix(new_size);
    double **A12 = allocate_matrix(new_size);
    double **A21 = allocate_matrix(new_size);
    double **A22 = allocate_matrix(new_size);
    double **B11 = allocate_matrix(new_size);
    double **B12 = allocate_matrix(new_size);
    double **B21 = allocate_matrix(new_size);
    double **B22 = allocate_matrix(new_size);
    double **C11 = allocate_matrix(new_size);
    double **C12 = allocate_matrix(new_size);
    double **C21 = allocate_matrix(new_size);
    double **C22 = allocate_matrix(new_size);

    // fill the submatrices
    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + new_size];
            A21[i][j] = A[i + new_size][j];
            A22[i][j] = A[i + new_size][j + new_size];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + new_size];
            B21[i][j] = B[i + new_size][j];
            B22[i][j] = B[i + new_size][j + new_size];
        }
    }

    double **M1 = allocate_matrix(new_size);
    double **M2 = allocate_matrix(new_size);
    double **M3 = allocate_matrix(new_size);
    double **M4 = allocate_matrix(new_size);
    double **M5 = allocate_matrix(new_size);
    double **M6 = allocate_matrix(new_size);
    double **M7 = allocate_matrix(new_size);
    double **T1 = allocate_matrix(new_size);
    double **T2 = allocate_matrix(new_size);

    add_matrices(A11, A22, T1, new_size);
    add_matrices(B11, B22, T2, new_size);
    strassen(T1, T2, M1, new_size);

    add_matrices(A21, A22, T1, new_size);
    strassen(T1, B11, M2, new_size);

    subtract_matrices(B12, B22, T1, new_size);
    strassen(A11, T1, M3, new_size);

    subtract_matrices(B21, B11, T1, new_size);
    strassen(A22, T1, M4, new_size);

    add_matrices(A11, A12, T1, new_size);
    strassen(T1, B22, M5, new_size);

    subtract_matrices(A21, A11, T1, new_size);
    add_matrices(B11, B12, T2, new_size);
    strassen(T1, T2, M6, new_size);

    subtract_matrices(A12, A22, T1, new_size);
    add_matrices(B21, B22, T2, new_size);
    strassen(T1, T2, M7, new_size);

    add_matrices(M1, M4, T1, new_size);
    subtract_matrices(T1, M5, T2, new_size);
    add_matrices(T2, M7, C11, new_size);

    add_matrices(M3, M5, C12, new_size);

    add_matrices(M2, M4, C21, new_size);

    subtract_matrices(M1, M2, T1, new_size);
    add_matrices(T1, M3, T2, new_size);
    add_matrices(T2, M6, C22, new_size);

    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + new_size] = C12[i][j];
            C[i + new_size][j] = C21[i][j];
            C[i + new_size][j + new_size] = C22[i][j];
        }
    }

    // free memory
    free_matrix(A11, new_size);
    free_matrix(A12, new_size);
    free_matrix(A21, new_size);
    free_matrix(A22, new_size);
    free_matrix(B11, new_size);
    free_matrix(B12, new_size);
    free_matrix(B21, new_size);
    free_matrix(B22, new_size);
    free_matrix(C11, new_size);
    free_matrix(C12, new_size);
    free_matrix(C21, new_size);
    free_matrix(C22, new_size);
    free_matrix(M1, new_size);
    free_matrix(M2, new_size);
    free_matrix(M3, new_size);
    free_matrix(M4, new_size);
    free_matrix(M5, new_size);
    free_matrix(M6, new_size);
    free_matrix(M7, new_size);
    free_matrix(T1, new_size);
    free_matrix(T2, new_size);
}