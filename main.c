#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "matrix_utils.h"
#include "matrix_multiply.h"
#include "matrix_multiply_blas.h"
#include "matrix_multiply_blocking.h"
#include "matrix_multiply_strassen.h"
#include "performance_utils.h"

int main()
{
  int sizes[] = {128, 512, 1024};
  //int sizes[] = {2};
  int block_sizes[] = {2, 4, 16, 64};

  int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
  int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);

  FILE *report = fopen("report/matrix_multiply_report.txt", "w");
  if (report == NULL)
  {
    printf("Erro ao abrir o arquivo de relatório.\n");
    return 1;
  }

  fprintf(report, "Relatório de Multiplicação de Matrizes\n");
  fprintf(report, "-------------------------------------\n");
  fprintf(report, "\n");

  for (int s = 0; s < num_sizes; s++)
  {
    int N = sizes[s];
    double **A = allocate_matrix(N);
    double **B = allocate_matrix(N);
    double **C = allocate_matrix(N);

    initialize_matrix(A, N);
    initialize_matrix(B, N);

    double cpu_time_used;
    double min_time = 1e30;
    double min_time_w_block = 1e30;
    double min_time_strassen = 1e30;
    double min_time_cblas = 1e30;
    const char *best_variation = "";
    int best_block_size = 0;

    fprintf(report, "\n-------------------------------------\n");
    fprintf(report, "Tamanho da matriz: %dx%d\n", N, N);
    fprintf(report, "-------------------------------------\n");
    fprintf(report, "\n");

    // ######### Multiplicação sem blocagem ###########

    fprintf(report, "Método sem blocagem\n");
    fprintf(report, "-------------------------------------\n");

    // Multiplicação ijk
    cpu_time_used = measure_time_no_blocking(matrix_multiply_ijk, A, B, C, N);

    fprintf(report, "Tempo gasto (ijk): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "ijk";
    }

    // Multiplicação ikj
    cpu_time_used = measure_time_no_blocking(matrix_multiply_ikj, A, B, C, N);

    fprintf(report, "Tempo gasto (ikj): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "ikj";
    }

    // Multiplicação jik
    cpu_time_used = measure_time_no_blocking(matrix_multiply_jik, A, B, C, N);

    fprintf(report, "Tempo gasto (jik): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "jik";
    }

    // Multiplicação jki
    cpu_time_used = measure_time_no_blocking(matrix_multiply_jki, A, B, C, N);

    fprintf(report, "Tempo gasto (jki): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "jki";
    }

    // Multiplicação kij
    cpu_time_used = measure_time_no_blocking(matrix_multiply_kij, A, B, C, N);

    fprintf(report, "Tempo gasto (kij): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "kij";
    }

    // Multiplicação kji
    cpu_time_used = measure_time_no_blocking(matrix_multiply_kji, A, B, C, N);

    fprintf(report, "Tempo gasto (kji): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "kji";
    }

    fprintf(report, "-------------------------------------\n");
    fprintf(report, "Melhor organização de laço para %dx%d: %s= %f segundos\n", N, N, best_variation, min_time);
    fprintf(report, "\n");

    fprintf(report, "Método com blocagem\n");
    fprintf(report, "-------------------------------------\n");

    // ################ Multiplicação usando Blocagem #################
    for (int b = 0; b < num_blocks; b++)
    {
      int block_size = block_sizes[b];

      if (strcmp(best_variation, "ijk") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_ijk, A, B, C, N, block_size);
      }
      else if (strcmp(best_variation, "ikj") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_ikj, A, B, C, N, block_size);
      }
      else if (strcmp(best_variation, "jik") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_jik, A, B, C, N, block_size);
      }
      else if (strcmp(best_variation, "jki") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_jki, A, B, C, N, block_size);
      }
      else if (strcmp(best_variation, "kij") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_kij, A, B, C, N, block_size);
      }
      else if (strcmp(best_variation, "kji") == 0)
      {
        cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking_kji, A, B, C, N, block_size);
      }

      fprintf(report, "Tamanho do bloco: %d, Variação: %s, Tempo: %f segundos\n",
              block_size, best_variation, cpu_time_used);

      if (cpu_time_used < min_time_w_block)
      {
        min_time_w_block = cpu_time_used;
        best_block_size = block_size;
      }
    }
    fprintf(report, "-------------------------------------\n");
    fprintf(report, "Melhor tamanho do bloco para %dx%d: %d= %f segundos\n", N, N, best_block_size, min_time_w_block);
    fprintf(report, "\n");

    // ########### Multiplicação usando o algoritmo de Strassen ###########
    // Multiplicação usando o algoritmo de Strassen
    printf("Multiplicação usando Strassen\n");
    cpu_time_used = measure_time_no_blocking(strassen, A, B, C, N);
    min_time_strassen = cpu_time_used;

    fprintf(report, "Multiplicação usando Strassen\n");
    fprintf(report, "-------------------------------------\n");
    fprintf(report, "Tempo gasto (Strassen): %f segundos\n", min_time_strassen);
    fprintf(report, "\n");

    // ########### Multiplicação usando CBLAS ###########
    // Multiplicação usando CBLAS
    printf("Multiplicação usando CBLAS\n");
    cpu_time_used = measure_time_no_blocking(matrix_multiply_cblas, A, B, C, N);
    min_time_cblas = cpu_time_used;

    fprintf(report, "Multiplicação usando CBLAS\n");
    fprintf(report, "-------------------------------------\n");
    fprintf(report, "Tempo gasto (CBLAS): %f segundos\n", min_time_cblas);
    fprintf(report, "\n");

    fprintf(report, "\n");
    fprintf(report, "Resultados:\n");
    fprintf(report, "-------------------------------------\n");
    fprintf(report, "\n");

    // Reporta a melhor organização de laço para o tamanho N
    fprintf(report, "Melhor organização de laço para %dx%d: %s= %f segundos\n", N, N, best_variation, min_time);

    // Reporta o tamanho do bloco mais eficiente para o tamanho N
    fprintf(report, "Melhor tamanho do bloco para %dx%d: %d= %f segundos\n", N, N, best_block_size, min_time_w_block);

    // Reporta o tempo gasto para o algoritmo de Strassen
    fprintf(report, "Tempo gasto (Strassen): %f segundos\n", min_time_strassen);

    // Reporta o tempo gasto para a multiplicação usando CBLAS
    fprintf(report, "Tempo gasto (CBLAS): %f segundos\n", min_time_cblas);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
  }

  fclose(report);
  printf("Relatório gerado com sucesso.\n");

  return 0;
}
