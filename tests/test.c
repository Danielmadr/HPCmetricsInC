#include <stdio.h>
#include <stdlib.h>
#include "../utils/matrix_utils.h"
#include "../utils/performance_utils.h"
#include "../src/mat_mult/matrix_multiply.h"
#include "../src/blocking/matrix_multiply_blocking.h"
#include "../src/cblas/matrix_multiply_blas.h"
#include "../src/strassen/matrix_multiply_strassen.h"

void test_func_generic(void (*func)(double **, double **, double **, int, void *, void *), double **A, double **B, double **C, double **R, int n, void *args, void *args2)
{
  reset_matrix(C, n);
  func(A, B, C, n, args, args2);
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
  return test_func_generic((void (*)(double **, double **, double **, int, void *, void *))func, A, B, C, R, n, NULL, NULL);
}

void test_func_blocking(void (*func)(double **, double **, double **, int, void *, void *), double **A, double **B, double **C, double **R, int n, int block_size, char *loop_order)
{
  return test_func_generic(func, A, B, C, R, n, (void *)&block_size, (void *)loop_order);
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
  int N = 128;

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

  // testa se o resultado da multiplicação é igual ao esperado
  test_func(matrix_multiply_ijk, pA, pB, pC, pR, N);
  test_func(matrix_multiply_ikj, pA, pB, pC, pR, N);
  test_func(matrix_multiply_jik, pA, pB, pC, pR, N);
  test_func(matrix_multiply_jki, pA, pB, pC, pR, N);
  test_func(matrix_multiply_kij, pA, pB, pC, pR, N);
  test_func(matrix_multiply_kji, pA, pB, pC, pR, N);

  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 1, "ijk");
  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 2, "ijk");
  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 3, "ijk");
  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 4, "ijk");
  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 5, "ijk");
  test_func_blocking(matrix_multiply_blocking, pA, pB, pC, pR, N, 6, "ijk");

  test_func(matrix_multiply_cblas, pA, pB, pC, pR, N);

  test_func(strassen, pA, pB, pC, pR, N);

  free_matrix(pA, N);
  free_matrix(pB, N);
  free_matrix(pC, N);
  free_matrix(pR, N);

  // to compile
  //  gcc -o test tests/test.c src/mat_mult/matrix_multiply.c src/blocking/matrix_multiply_blocking.c src/cblas/matrix_multiply_blas.c src/strassen/matrix_multiply_strassen.c utils/matrix_utils.c utils/performance_utils.c -lm

  return 0;
}
