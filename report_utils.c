#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "papi.h"

void report_header(FILE *report)
{
  fprintf(report, "Relatório de Multiplicação de Matrizes\n");
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  fprintf(report, "Data: %02d-%02d-%d %02d:%02d:%02d\n",
          tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
          tm.tm_hour, tm.tm_min, tm.tm_sec);
  fprintf(report, "-------------------------------------\n");
  fprintf(report, "\n");
}

void report_info(FILE *report, int matrix_size, char *method, int num_blocks)
{
  fprintf(report, "\n-------------------------------------\n");
  fprintf(report, "Tamanho da matriz: %dx%d\n", matrix_size, matrix_size);
  if (num_blocks > 0)
  {
    fprintf(report, "Número de blocos: %d\n", num_blocks);
  }
  fprintf(report, "Método: %s \n", method);
  fprintf(report, "-------------------------------------");
  fprintf(report, "\n");
}

void report_body(FILE *report, int events[], int num_events, long long *results, char *method)
{
  fprintf(report, "\nMétodo: %s\n", method);

  // print time
  double real_time = (double)results[num_events + 1] / 1000000.0;
  double cpu_time = (double)results[num_events + 2] / (double)PAPI_get_real_cyc();
  fprintf(report, "Tempo real: %.6f segundos\n", real_time);
  fprintf(report, "Tempo de CPU: %.6f segundos\n", cpu_time);

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

  // Calculate MFLOPS
  double mflops = results[4]               // total of operations
                  / (real_time * 1000000); // time in seconds
  fprintf(report, "MFLOPS \u2248 %.2f\n", mflops);

  // Calculate CPI
  double cpi = (double)results[3] / (double)results[4];
  fprintf(report, "CPI: %.2f\n", cpi);
}
