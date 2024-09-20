#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "papi.h"
#include "../utils/matrix_utils.h"
#include "mat_mult/matrix_multiply.h"
#include "cblas/matrix_multiply_blas.h"
#include "blocking/matrix_multiply_blocking.h"
#include "strassen/matrix_multiply_strassen.h"
#include "../utils/performance_utils.h"
#include "../utils/report_utils.h"

//* Global variables
int matrix_sizes[] = {128 , 512, 1024}; // Matrix sizes
int block_sizes[] = {2 , 4, 16, 64};    // Block sizes

// PAPI events
#define NUM_EVENTS 6
int eventos[] = {
    PAPI_L1_TCM,  // L1 cache misses
    PAPI_L2_TCM,  // L2 cache misses
    PAPI_L3_TCM,  // L3 cache misses
    PAPI_TOT_CYC, // Total cycles
    PAPI_TOT_INS, // Total instructions
    PAPI_FP_OPS   // Total floating point operations
};

// Struct to store the results
typedef struct
{
  char *method;
  long long metrics[NUM_EVENTS];
  double time[2];
} Result;

// Function to calculate the best method
void best_method(Result *results, int num_results)
{
  int best_method_index = 0;

  for (int i = 1; i < num_results-1; i++)
  {
    if (results[i].time[0] < results[best_method_index].time[0])
    {
      best_method_index = i;
    }
  }

  results[num_results - 1].method =  results[best_method_index].method;
  results[num_results - 1].time[0] = results[best_method_index].time[0]; 
  results[num_results - 1].time[1] = results[best_method_index].time[1]; 

  for (int j = 0; j < NUM_EVENTS; j++)
  {
    results[num_results - 1].metrics[j] = results[best_method_index].metrics[j];
  }
}

int main()
{
  const int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
  const int num_blocks = sizeof(block_sizes) / sizeof(block_sizes[0]);

  FILE *report = fopen("../report/matrix_multiply_report.txt", "w");
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

    // Results for methods without blocking
    Result results[7];
    results[0].method = "ijk";
    results[1].method = "ikj";
    results[2].method = "jik";
    results[3].method = "jki";
    results[4].method = "kij";
    results[5].method = "kji";
    results[6].method = "best_method";
    char *best_loop_order;

    // Results for methods with blocking
    Result results_w_block[5];
    results_w_block[0].method = "2 blocos";
    results_w_block[1].method = "4 blocos";
    results_w_block[2].method = "16 blocos";
    results_w_block[3].method = "64 blocos";
    results_w_block[4].method = "best_method";

    // Results for Strassen
    Result results_strassen;
    results_strassen.method = "Strassen";

    // Results for CBLAS
    Result results_cblas;
    results_cblas.method = "CBLAS";

    
    report_info(report, N);

    // Measure time for each method without blocking
    report_method(report, "Sem blocagem");

    // Measure time methods without blocking and loop order ijk
    avaliar_funcao_sem_block(matrix_multiply_ijk, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[0].metrics, results[0].time, results[0].method);

    // Measure time methods without blocking and loop order ikj
    avaliar_funcao_sem_block(matrix_multiply_ikj, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[1].metrics, results[1].time, results[1].method);

    // Measure time methods without blocking and loop order jik
    avaliar_funcao_sem_block(matrix_multiply_jik, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[2].metrics, results[2].time, results[2].method);

    // Measure time methods without blocking and loop order jki
    avaliar_funcao_sem_block(matrix_multiply_jki, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[3].metrics, results[3].time, results[3].method);

    // Measure time methods without blocking and loop order kij
    avaliar_funcao_sem_block(matrix_multiply_kij, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[4].metrics, results[4].time, results[4].method);

    // Measure time methods without blocking and loop order kji
    avaliar_funcao_sem_block(matrix_multiply_kji, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results[5].metrics, results[5].time, results[5].method);

    // Calculate the best method
    best_method(results, 7);
    best_loop_order = results[6].method;

    // Print results
    for (int i = 0; i < 6; i++)
    {
      report_body(report, eventos, NUM_EVENTS, results[i].method, results[i].metrics, results[i].time);
    }

    // Measure time for each method with blocking
    report_method(report, "Com blocagem");

    // Measure time methods with blocking and loop order best mesured without blocking
    for (int b = 0; b < num_blocks; b++)
    {
      int block_size = block_sizes[b];
      avaliar_funcao_com_block(matrix_multiply_blocking, eventos, NUM_EVENTS, A, B, C, N, block_size, best_loop_order, results_w_block[b].metrics, results_w_block[b].time, results_w_block[b].method);
    }

    // Calculate the best block configuration
    best_method(results_w_block, num_blocks + 1);

    // Print results
    for (int i = 0; i < num_blocks + 1; i++)
    {
      report_body(report, eventos, NUM_EVENTS, results_w_block[i].method, results_w_block[i].metrics, results_w_block[i].time);
    }
    
    // Measure time for Strassen
    report_method(report, "Strassen");

    avaliar_funcao_sem_block(strassen, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results_strassen.metrics, results_strassen.time, results_strassen.method);
    report_body(report, eventos, NUM_EVENTS, results_strassen.method, results_strassen.metrics, results_strassen.time);

    // Measure time for CBLAS
    report_method(report, "CBLAS");

    avaliar_funcao_sem_block(matrix_multiply_cblas, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, results_cblas.metrics, results_cblas.time, results_cblas.method);
    report_body(report, eventos, NUM_EVENTS, results_cblas.method, results_cblas.metrics, results_cblas.time);

    // Print resume of the best methods
    report_general_results(report, results[6].method, results[6].metrics, results[6].time[0], results_w_block[4].method, results_w_block[4].metrics, results_w_block[4].time[0], results_strassen.method, results_strassen.metrics, results_strassen.time[0], results_cblas.method, results_cblas.metrics, results_cblas.time[0]);

    // Free matrices
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);
  }

  fclose(report);
  printf("Repot generated succesfully!\n");

  return 0;
}
