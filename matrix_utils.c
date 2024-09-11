#include <stdio.h>
#include <stdlib.h>

// allocate memory for a matrix
double **allocate_matrix(int n)
{
  double **matrix = (double **)malloc(n * sizeof(double *));
  if (matrix == NULL)
  {
    printf("Erro ao alocar memória para a matriz.\n");
    exit(1);
  }
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (double *)malloc(n * sizeof(double));
    if (matrix[i] == NULL)
    {
      printf("Erro ao alocar memória para a matriz.\n");
      exit(1);
    }
  }
  return matrix;
}

// free memory for a matrix
void free_matrix(double **matrix, int N)
{
  for (int i = 0; i < N; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

// initialize a matrix with random values
void initialize_matrix(double **matrix, int N)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      matrix[i][j] = rand() % 100;
    }
  }
}

// print a matrix
void print_matrix(double **matrix, int N)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%.1f ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// reset a matrix to zero
void reset_matrix(double **matrix, int N)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      matrix[i][j] = 0;
    }
  }
}

// compare two matrices
int compare_matrices(double **A, double **B, int N)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (A[i][j] != B[i][j])
      {
        return 0;
      }
    }
  }
  return 1;
}
