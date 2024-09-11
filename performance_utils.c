#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_utils.h"
#include "papi.h"

// Função para avaliar uma função e retornar os resultados PAPI
void avaliar_funcao(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                    double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados)
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
  printf("real_time nocod: %f\n", real_time);
  double cpu_time = (double)(end_time_cpu - start_time_cpu) / (double)PAPI_get_real_cyc(); // Divide pelos ciclos por segundo
  printf("cpu_time nocod: %f\n", cpu_time);

  // Armazena os tempos no array resultados
  resultados[NUM_EVENTS + 1] = end_time_real - start_time_real;
  resultados[NUM_EVENTS + 2] = end_time_cpu - start_time_cpu;

  // Libera o EventSet
  PAPI_cleanup_eventset(EventSet);
}

// Implementação da função genérica
double measure_time_generic(void (*multiply_func)(double **, double **, double **, int, void *, void *),
                            double **A, double **B, double **C, int N, void *extra_data, void *extra_data2)
{
  if (!A || !B || !C || !multiply_func || N <= 0)
  {
    fprintf(stderr, "Invalid input to measure_time function.\n");
    return -1.0;
  }

  reset_matrix(C, N);
  // printf("_____________________________\ncomeço\n");
  // print_matrix(C, N); // Somente se necessário

  clock_t start, end;
  start = clock();
  multiply_func(A, B, C, N, extra_data, extra_data2);
  end = clock();

  // printf("fim\n");
  // print_matrix(A, N); // Somente se necessário
  // print_matrix(B, N); // Somente se necessário
  // print_matrix(C, N); // Somente se necessário
  // printf("____________________________fim\n");

  return ((double)(end - start)) / CLOCKS_PER_SEC;
}

// Para funções sem blocagem e sem extra_data
double measure_time_no_blocking(void (*multiply_func)(double **, double **, double **, int),
                                double **A, double **B, double **C, int N)
{
  return measure_time_generic((void (*)(double **, double **, double **, int, void *, void *))multiply_func, A, B, C, N, NULL, NULL);
}

// Para funções com blocagem e com extra_data
double measure_time_with_blocking(void (*multiply_func)(double **, double **, double **, int, void *, void *),
                                  double **A, double **B, double **C, int N, int block_size, char *loop_order)
{
  // printf("block_size: %d\n", block_size);
  return measure_time_generic(multiply_func, A, B, C, N, (void *)&block_size, (void *)loop_order);
}

// função teste com blocagem
void avaliar_funcao_com_block(void (*multiply_func)(double **, double **, double **, int, void *, void *), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, int block_size, char *loop_order, long long *resultados)
{
  return avaliar_funcao(multiply_func, eventos, NUM_EVENTS, A, B, C, N, (void *)&block_size, (void *)loop_order, resultados);
}

// função teste sem blocagem
void avaliar_funcao_sem_block(void (*multiply_func)(double **, double **, double **, int), int eventos[], int NUM_EVENTS,
                              double **A, double **B, double **C, int N, void *extra_data, void *extra_data2, long long *resultados)
{
  return avaliar_funcao((void (*)(double **, double **, double **, int, void *, void *))multiply_func, eventos, NUM_EVENTS, A, B, C, N, NULL, NULL, resultados);
}