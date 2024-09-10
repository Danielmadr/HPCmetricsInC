#include <stdio.h>
#include <stdlib.h>

// Função para alocar memória para uma matriz
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

// Função para liberar a memória alocada para a matriz
void free_matrix(double **matrix, int N)
{
  for (int i = 0; i < N; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

// Inicializa a matriz com valores aleatórios
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

// Função para imprimir a matriz
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

// Função para resetar a matriz
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

// Compara duas matrizes
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
