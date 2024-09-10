#include <stdio.h>
#include <stdlib.h>
#include "matrix_utils.h"
#include "matrix_multiply.h"
#include "matrix_multiply_blas.h"
#include "matrix_multiply_blocking.h"
#include "matrix_multiply_strassen.h"
#include "performance_utils.h"

void test_func_generic(void (*func)(double **, double **, double **, int, void *), double **A, double **B, double **C, double **R, int n, void *args)
{
  reset_matrix(C, n);
  func(A, B, C, n, args);
  if (compare_matrices(C, R, n))
  {
    printf("Teste passou\n");
  }
  else
  {
    printf("Teste falhou\n");
  }
}

void test_func(void (*func)(double **, double **, double **, int), double **A, double **B, double **C, double **R, int n)
{
  return test_func_generic((void (*)(double **, double **, double **, int, void *))func, A, B, C, R, n, NULL);
}

void test_func_blocking(void (*func)(double **, double **, double **, int, void *), double **A, double **B, double **C, double **R, int n, int block_size)
{
  return test_func_generic(func, A, B, C, R, n, (void *)&block_size);
}

void copy_matrix(double **A, double **B, int N)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      B[i][j] = A[i][j];
    }
  }
}

int main(int argc, char const *argv[])
{
  // ################## Testes randomico para matrizes grandes ##################
  int N = 24;

  double **pA = allocate_matrix(N);
  double **pB = allocate_matrix(N);
  double **pC = allocate_matrix(N);
  double **pR = allocate_matrix(N);

  initialize_matrix(pA, N);
  initialize_matrix(pB, N);

  matrix_multiply_cblas(pA, pB, pC, N);
  copy_matrix(pC, pR, N);

  /*//################## Testes para matrizes pequenas ##################
  const int N = 2;

  double A[2][2] = {2.0, 4.0,
                     1.0, 5.0};

  double B[2][2] = {3.0, 1.0,
                    1.0, 0.0};

  double C[2][2] = {0.0};

  double R[2][2] = {10.0, 2.0,
                    8.0, 1.0};

  // Criando ponteiros para os arrays bidimensionais
  double *pA[N];
  double *pB[N];
  double *pC[N];
  double *pR[N];

  //Configurando os ponteiros para apontar para as linhas de cada array
  for (int i = 0; i < N; i++)
  {
    pA[i] = A[i];
    pB[i] = B[i];
    pC[i] = C[i];
    pR[i] = R[i];
  }*/

  //testa se o resultado da multiplicação é igual ao esperado
  test_func(matrix_multiply_ijk, pA, pB, pC, pR, N);
  test_func(matrix_multiply_ikj, pA, pB, pC, pR, N);
  test_func(matrix_multiply_jik, pA, pB, pC, pR, N);
  test_func(matrix_multiply_jki, pA, pB, pC, pR, N);
  test_func(matrix_multiply_kij, pA, pB, pC, pR, N);
  test_func(matrix_multiply_kji, pA, pB, pC, pR, N);

  test_func_blocking(matrix_multiply_blocking_ijk, pA, pB, pC, pR, N, 1);
  test_func_blocking(matrix_multiply_blocking_ikj, pA, pB, pC, pR, N, 2);
  test_func_blocking(matrix_multiply_blocking_jik, pA, pB, pC, pR, N, 3);
  test_func_blocking(matrix_multiply_blocking_jki, pA, pB, pC, pR, N, 4);
  test_func_blocking(matrix_multiply_blocking_kij, pA, pB, pC, pR, N, 5);
  test_func_blocking(matrix_multiply_blocking_kji, pA, pB, pC, pR, N, 6);

  test_func(matrix_multiply_cblas, pA, pB, pC, pR, N);

  test_func(strassen, pA, pB, pC, pR, N);

  free_matrix(pA, N);
  free_matrix(pB, N);
  free_matrix(pC, N);
  free_matrix(pR, N);

  return 0;
}
