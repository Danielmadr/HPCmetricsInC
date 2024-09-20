#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "papi.h"

// Function to print the report header
void report_header(FILE *report)
{
  fprintf(report, "Relatório de Multiplicação de Matrizes       ");
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  fprintf(report, "Data: %02d-%02d-%d %02d:%02d:%02d\n",
          tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
          tm.tm_hour, tm.tm_min, tm.tm_sec);
  fprintf(report, "-----------------------------------------------------------------------------------------------------------------\n");
  fprintf(report, "\n");
}

// Function to print the report header
void report_info(FILE *report, int matrix_size)
{
  fprintf(report, "-----------------------------------------------------------------------------------------------------------------\n");
  fprintf(report, "Tamanho da matriz: %dx%d\n", matrix_size, matrix_size);
  fprintf(report, "-----------------------------------------------------------------------------------------------------------------");
  fprintf(report, "\n");
}

// Function to print methos
void report_method(FILE *report, char *method)
{
  fprintf(report, "\nMétodo: %s\n", method);
  fprintf(report, "-------------------------------------------");
  fprintf(report, "\n");
}

// Function to print the report body
void report_body(FILE *report, int events[], int num_events, char *method, long long *results, double *time)
{
  fprintf(report, "\nMétodo: %s\n", method);

  // print time
  fprintf(report, "Tempo real: %.6f segundos\n", time[0]);
  fprintf(report, "Tempo de CPU: %.6f segundos\n", time[1]);

  // print the events values
  char event_name[PAPI_MAX_STR_LEN]; // Array to store the event name
  for (int i = 0; i < num_events; i++)
  {
    if (PAPI_event_code_to_name(events[i], event_name) != PAPI_OK)
    {
      fprintf(stderr, "Erro ao obter o nome do evento PAPI.\n");
      continue;
    }
    fprintf(report, "%s: %lld\n", event_name, results[i]);
  }

  // Calculate CPI
  double cpi = (double)results[3] / (double)results[4];
  fprintf(report, "CPI: %.2f\n", cpi);

  // Calculate MFLOPS
  double mflops = (double)results[5] / time[0] / 1e6;
  fprintf(report, "MFLOPS: %.2f\n", mflops);
  
}

void report_general_results(FILE *report, char *method, long long *results, double min_time, char *method_w_block, long long *results_w_block, double min_time_w_block, char *method_strassen, long long *results_strassen, double min_time_strassen, char *method_cblas, long long *results_cblas, double min_time_cblas)
{
  fprintf(report, "\n\n");
  fprintf(report, "-------------------------------------------\n");
  fprintf(report, "Resultados Gerais\n");
  fprintf(report, "-------------------------------------------\n");

  fprintf(report, "Melhor método sem blocagem: %s\n", method);
  fprintf(report, "Tempo real: %.6f segundos\n", min_time);
  fprintf(report, "-------------------------------------------\n");

  fprintf(report, "Melhor método com blocagem: %s\n", method_w_block);
  fprintf(report, "Tempo real: %.6f segundos\n", min_time_w_block);
  fprintf(report, "-------------------------------------------\n");

  fprintf(report, "Melhor método Strassen: %s\n", method_strassen);
  fprintf(report, "Tempo real: %.6f segundos\n", min_time_strassen);
  fprintf(report, "-------------------------------------------\n");

  fprintf(report, "Melhor método CBLAS: %s\n", method_cblas);
  fprintf(report, "Tempo real: %.6f segundos\n", min_time_cblas);
  fprintf(report, "-------------------------------------------\n");
}