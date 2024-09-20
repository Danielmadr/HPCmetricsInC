#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "matrix_utils.h"
#include "papi.h"

// Função para avaliar uma função e retornar os resultados PAPI
void avaliar_funcao(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                    double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados, double *time, char *method)
{
  // Inicializa a biblioteca PAPI
  if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
  {
    fprintf(stderr, "Erro ao inicializar PAPI.\n");
    exit(1);
  }

  // Cria um EventSet
  int EventSet = PAPI_NULL;
  if (PAPI_create_eventset(&EventSet) != PAPI_OK)
  {
    fprintf(stderr, "Erro ao criar EventSet.\n");
    exit(1);
  }

  // Verifica se PAPI_FP_OPS é suportado e adiciona eventos ao EventSet
  if (PAPI_query_event(PAPI_FP_OPS) == PAPI_OK)
  {
    if (PAPI_add_events(EventSet, eventos, NUM_EVENTS) != PAPI_OK)
    {
      fprintf(stderr, "Erro ao adicionar eventos ao EventSet.\n");
      exit(1);
    }
  }
  else
  {
    if (PAPI_add_events(EventSet, eventos, NUM_EVENTS - 1) != PAPI_OK)
    {
      fprintf(stderr, "Erro ao adicionar eventos ao EventSet.\n");
      exit(1);
    }
    resultados[NUM_EVENTS - 1] = -1;
    printf("PAPI_FP_OPS não é suportado. Informações de operações de ponto flutuante não serão coletadas.\n");
  }

  // Inicia a contagem dos eventos
  if (PAPI_start(EventSet) != PAPI_OK)
  {
    fprintf(stderr, "Erro ao iniciar a contagem dos eventos.\n");
    exit(1);
  }

  // Registra o tempo de início
  long long start_time_real = PAPI_get_real_usec(); // Tempo real em microsegundos
  long long start_time_cpu = PAPI_get_real_cyc();   // Tempo de CPU em ciclos

  // Executa a função passada como argumento
  multiply_func(A, B, C, N, extra_data, extra_data2);

  // Registra o tempo de término
  long long end_time_real = PAPI_get_real_usec(); // Tempo real em microsegundos
  long long end_time_cpu = PAPI_get_real_cyc();   // Tempo de CPU em ciclos

  // Para a contagem dos eventos e obtém os valores
  if (PAPI_stop(EventSet, resultados) != PAPI_OK)
  {
    fprintf(stderr, "Erro ao parar a contagem dos eventos.\n");
    exit(1);
  }

  // Calcula o tempo de execução real e de CPU em segundos
  double real_time = (double)(end_time_real - start_time_real) / 1000000.0;
  double cpu_time = (double)(end_time_cpu - start_time_cpu) / (double)PAPI_get_real_cyc(); // Divide pelos ciclos por segundo

  // Armazena os tempos no array resultados
  time[0] = real_time;
  time[1] = cpu_time;

  // Calcula o número de operações de ponto flutuante
  if (resultados[NUM_EVENTS - 1] == -1)
  {
    if (strcmp(method, "Strassen") == 0)
    {
      // 7 multiplicações de matrizes menores e O(N^2) operações de soma/subtração
      resultados[NUM_EVENTS - 1] = (pow(N, log2(7)) + pow(N, 2));
    }
    else
    {
      // Método tradicional: 2 * N^3 multiplicações de ponto flutuante
      resultados[NUM_EVENTS - 1] = (2 * pow(N, 3));
    }
  }

  // Libera o EventSet
  PAPI_cleanup_eventset(EventSet);
}

// função teste com blocagem
void avaliar_funcao_com_block(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, int block_size, char *loop_order, long long *resultados, double *time, char *method)
{
  return avaliar_funcao(multiply_func, eventos, NUM_EVENTS, A, B, C, N, (void *)&block_size, (void *)loop_order, resultados, time, method);
}

// função teste sem blocagem
void avaliar_funcao_sem_block(void (*multiply_func)(double **, double **, double **, int), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados, double *time, char *method)
{
  return avaliar_funcao((void (*)(double **, double **, double **, int, void *, void *))multiply_func, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados, time, method);
}