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
#include "papi.h"
#include "report_utils.h"

//* Global variables
int matrix_sizes[] = {128 /*, 512/*, 1024*/}; // matriz sizes
int block_sizes[] = {/*2, 4,*/ 16 /*, 64*/};  // block sizes
// Eventos PAPI
#define NUM_EVENTS 6
int eventos[] = {
    PAPI_L1_TCM,  // Misses de cache de nível 1
    PAPI_L2_TCM,  // Misses de cache de nível 2
    PAPI_L3_TCM,  // Misses de cache de nível 3
    PAPI_TOT_CYC, // Ciclos de clock totais
    PAPI_TOT_INS, // Instruções totais
    PAPI_FP_OPS   // Operações de ponto flutuante (se suportado)
};

void best_method(char *method, long long exe_time, char **best_method, double *best_time)
{
  double exe_time_d = (double)exe_time / 1000000.0;

  // Comparando o valor apontado por best_time
  if (exe_time_d < *best_time)
  {
    *best_time = exe_time_d; // Atualizando o valor apontado por best_time
    *best_method = method;   // Atualizando o método vencedor
  }
}

int main()
{
  const int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
  const int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);

  FILE *report = fopen("report/matrix_multiply_report.txt", "w");
  if (report == NULL)
  {
    printf("Erro ao abrir o arquivo de relatório.\n");
    return 1;
  }

  // Print report header
  report_header(report);

  for (int s = 0; s < num_sizes; s++)
  {
    int N = matrix_sizes[s];
    double **A = allocate_matrix(N);
    double **B = allocate_matrix(N);
    double **C = allocate_matrix(N);

    initialize_matrix(A, N);
    initialize_matrix(B, N);

    double cpu_time_used;
    long long resultados[NUM_EVENTS + 2] = {0};
    double min_time = 1e30;
    double min_time_w_block = 1e30;
    double min_time_strassen = 1e30;
    double min_time_cblas = 1e30;
    char *best_variation = "";
    int best_block_size = 0;
    double min_time_papi = 1e30;
    char *best_variation_papi = "";

    report_info(report, N, "Sem blocagem", 0);

    //* ######### Multiplicação sem blocagem ###########
    // Multiplicação ijk
    cpu_time_used = measure_time_no_blocking(matrix_multiply_ijk, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_ijk, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "ijk");
    best_method("ijk", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);
    

    fprintf(report, "Tempo gasto (ijk): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "ijk";
    }

    // Multiplicação ikj
    cpu_time_used = measure_time_no_blocking(matrix_multiply_ikj, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_ikj, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "ikj");
    best_method("ikj", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);

    fprintf(report, "Tempo gasto (ikj): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "ikj";
    }

    // Multiplicação jik
    cpu_time_used = measure_time_no_blocking(matrix_multiply_jik, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_jik, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "jik");
    best_method("jik", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);

    fprintf(report, "Tempo gasto (jik): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "jik";
    }

    // Multiplicação jki
    cpu_time_used = measure_time_no_blocking(matrix_multiply_jki, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_jki, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "jki");
    best_method("jki", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);

    fprintf(report, "Tempo gasto (jki): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "jki";
    }

    // Multiplicação kij
    cpu_time_used = measure_time_no_blocking(matrix_multiply_kij, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_kij, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "kij");
    best_method("kij", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);

    fprintf(report, "Tempo gasto (kij): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "kij";
    }

    // Multiplicação kji
    cpu_time_used = measure_time_no_blocking(matrix_multiply_kji, A, B, C, N);
    avaliar_funcao_sem_block(matrix_multiply_kji, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
    report_body(report, eventos, NUM_EVENTS, resultados, "kji");
    best_method("kji", resultados[NUM_EVENTS + 1], &best_variation_papi, &min_time_papi);

    fprintf(report, "Tempo gasto (kji): %f segundos\n", cpu_time_used);
    if (cpu_time_used < min_time)
    {
      min_time = cpu_time_used;
      best_variation = "kji";
    }

    fprintf(report, "-------------------------------------\n");
    fprintf(report, "Melhor organização de laço para %dx%d: %s= %f segundos\n", N, N, best_variation, min_time);
    fprintf(report, "\n");

    fprintf(report, "-------------------------------------\n");
    fprintf(report, "PAPI: Melhor organização de laço para %dx%d: %s= %f segundos\n", N, N, best_variation_papi, min_time_papi);

    // ################ Multiplicação usando Blocagem #################
    for (int b = 0; b < num_blocks; b++)
    {
      report_info(report, N, "Com blocagem", num_blocks);

      int block_size = block_sizes[b];

      cpu_time_used = measure_time_with_blocking(matrix_multiply_blocking, A, B, C, N, block_size, best_variation);

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

    // teste papi
    avaliar_funcao_com_block(matrix_multiply_blocking, eventos, NUM_EVENTS, A, B, C, N, 2, best_variation, resultados);

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
  }

  fclose(report);
  printf("Relatório gerado com sucesso.\n");

  return 0;
}
