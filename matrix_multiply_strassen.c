#include <stdio.h>
#include <stdlib.h>
#include "matrix_utils.h"

int cont = 0;
// // Função para alocar memória para uma matriz de tamanho n x n
// double** allocate_matrix(int n) {
//     double **matrix = (double **)malloc(n * sizeof(double *));
//     for (int i = 0; i < n; i++) {
//         matrix[i] = (double *)malloc(n * sizeof(double));
//     }
//     return matrix;
// }

// Função para adicionar duas matrizes A e B de tamanho n x n, armazenando o resultado em C
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

// Função para subtrair duas matrizes A e B de tamanho n x n, armazenando o resultado em C
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

// Implementação do algoritmo de Strassen
void strassen(double **A, double **B, double **C, int n)
{
    if (n <= 32)
    { // Conventional multiplication for small matrices
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

    // Preencher as submatrizes
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

    // Libere a memória das matrizes temporárias
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

// #include <stdio.h>
// #include <stdlib.h>

// // Função para alocar memória para uma matriz
// double** alocarMatriz(int n) {
//     double** matriz = (double**)malloc(n * sizeof(double*));
//     for (int i = 0; i < n; i++) {
//         matriz[i] = (double*)malloc(n * sizeof(double));
//     }
//     return matriz;
// }

// // Função para liberar a memória de uma matriz
// void liberarMatriz(double** matriz, int n) {
//     for (int i = 0; i < n; i++) {
//         free(matriz[i]);
//     }
//     free(matriz);
// }

// // Função para adicionar duas matrizes
// void adicionarMatrizes(double** A, double** B, double** C, int n) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             C[i][j] = A[i][j] + B[i][j];
//         }
//     }
// }

// // Função para subtrair duas matrizes
// void subtrairMatrizes(double** A, double** B, double** C, int n) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             C[i][j] = A[i][j] - B[i][j];
//         }
//     }
// }

// // Função de multiplicação de Strassen
// void strassen_multiply(double** A, double** B, double** C, int n) {
//     if (n == 1) {
//         C[0][0] = A[0][0] * B[0][0];
//         return;
//     }

//     int newSize = n / 2;
//     double** A11 = alocarMatriz(newSize);
//     double** A12 = alocarMatriz(newSize);
//     double** A21 = alocarMatriz(newSize);
//     double** A22 = alocarMatriz(newSize);
//     double** B11 = alocarMatriz(newSize);
//     double** B12 = alocarMatriz(newSize);
//     double** B21 = alocarMatriz(newSize);
//     double** B22 = alocarMatriz(newSize);
//     double** C11 = alocarMatriz(newSize);
//     double** C12 = alocarMatriz(newSize);
//     double** C21 = alocarMatriz(newSize);
//     double** C22 = alocarMatriz(newSize);
//     double** M1 = alocarMatriz(newSize);
//     double** M2 = alocarMatriz(newSize);
//     double** M3 = alocarMatriz(newSize);
//     double** M4 = alocarMatriz(newSize);
//     double** M5 = alocarMatriz(newSize);
//     double** M6 = alocarMatriz(newSize);
//     double** M7 = alocarMatriz(newSize);
//     double** temp1 = alocarMatriz(newSize);
//     double** temp2 = alocarMatriz(newSize);

//     // Dividir as matrizes A e B em submatrizes
//     for (int i = 0; i < newSize; i++) {
//         for (int j = 0; j < newSize; j++) {
//             A11[i][j] = A[i][j];
//             A12[i][j] = A[i][j + newSize];
//             A21[i][j] = A[i + newSize][j];
//             A22[i][j] = A[i + newSize][j + newSize];
//             B11[i][j] = B[i][j];
//             B12[i][j] = B[i][j + newSize];
//             B21[i][j] = B[i + newSize][j];
//             B22[i][j] = B[i + newSize][j + newSize];
//         }
//     }

//     // M1 = (A11 + A22) * (B11 + B22)
//     adicionarMatrizes(A11, A22, temp1, newSize);
//     adicionarMatrizes(B11, B22, temp2, newSize);
//     strassen_multiply(temp1, temp2, M1, newSize);

//     // M2 = (A21 + A22) * B11
//     adicionarMatrizes(A21, A22, temp1, newSize);
//     strassen_multiply(temp1, B11, M2, newSize);

//     // M3 = A11 * (B12 - B22)
//     subtrairMatrizes(B12, B22, temp1, newSize);
//     strassen_multiply(A11, temp1, M3, newSize);

//     // M4 = A22 * (B21 - B11)
//     subtrairMatrizes(B21, B11, temp1, newSize);
//     strassen_multiply(A22, temp1, M4, newSize);

//     // M5 = (A11 + A12) * B22
//     adicionarMatrizes(A11, A12, temp1, newSize);
//     strassen_multiply(temp1, B22, M5, newSize);

//     // M6 = (A21 - A11) * (B11 + B12)
//     subtrairMatrizes(A21, A11, temp1, newSize);
//     adicionarMatrizes(B11, B12, temp2, newSize);
//     strassen_multiply(temp1, temp2, M6, newSize);

//     // M7 = (A12 - A22) * (B21 + B22)
//     subtrairMatrizes(A12, A22, temp1, newSize);
//     adicionarMatrizes(B21, B22, temp2, newSize);
//     strassen_multiply(temp1, temp2, M7, newSize);

//     // C11 = M1 + M4 - M5 + M7
//     adicionarMatrizes(M1, M4, temp1, newSize);
//     subtrairMatrizes(temp1, M5, temp2, newSize);
//     adicionarMatrizes(temp2, M7, C11, newSize);

//     // C12 = M3 + M5
//     adicionarMatrizes(M3, M5, C12, newSize);

//     // C21 = M2 + M4
//     adicionarMatrizes(M2, M4, C21, newSize);

//     // C22 = M1 - M2 + M3 + M6
//     subtrairMatrizes(M1, M2, temp1, newSize);
//     adicionarMatrizes(temp1, M3, temp2, newSize);
//     adicionarMatrizes(temp2, M6, C22, newSize);

//     // Combinar as submatrizes em C
//     for (int i = 0; i < newSize; i++) {
//         for (int j = 0; j < newSize; j++) {
//             C[i][j] = C11[i][j];
//             C[i][j + newSize] = C12[i][j];
//             C[i + newSize][j] = C21[i][j];
//             C[i + newSize][j + newSize] = C22[i][j];
//         }
//     }

//     // Liberar memória
//     liberarMatriz(A11, newSize);
//     liberarMatriz(A12, newSize);
//     liberarMatriz(A21, newSize);
//     liberarMatriz(A22, newSize);
//     liberarMatriz(B11, newSize);
//     liberarMatriz(B12, newSize);
//     liberarMatriz(B21, newSize);
//     liberarMatriz(B22, newSize);
//     liberarMatriz(C11, newSize);
//     liberarMatriz(C12, newSize);
//     liberarMatriz(C21, newSize);
//     liberarMatriz(C22, newSize);
//     liberarMatriz(M1, newSize);
//     liberarMatriz(M2, newSize);
//     liberarMatriz(M3, newSize);
//     liberarMatriz(M4, newSize);
//     liberarMatriz(M5, newSize);
//     liberarMatriz(M6, newSize);
//     liberarMatriz(M7, newSize);
//     liberarMatriz(temp1, newSize);
//     liberarMatriz(temp2, newSize);
// }