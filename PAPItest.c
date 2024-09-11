#include <stdio.h>
#include <stdlib.h>
#include <papi.h>

#define NUM_EVENTS 6

// Define a função de teste
void test_function()
{
  // Código de teste (neste caso, apenas um loop simples)
  for (int i = 0; i < 1000000; i++)
  {
    int a = i * 2;
    int b = a + 1;
    // ... qualquer outra operação que deseja medir ...
  }
}

int main()
{
  // Inicializa a biblioteca PAPI
  if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
  {
    fprintf(stderr, "Erro ao inicializar PAPI.\n");
    exit(1);
  }

  // Define os eventos PAPI que você deseja medir
  int events[NUM_EVENTS] = {
      PAPI_L1_TCM,  // Misses de cache de nível 1
      PAPI_L2_TCM,  // Misses de cache de nível 2
      PAPI_L3_TCM,  // Misses de cache de nível 3
      PAPI_TOT_CYC, // Ciclos de clock totais
      PAPI_TOT_INS, // Instruções totais
      PAPI_FP_OPS   // Operações de ponto flutuante (se suportado)
  };

  // Declara variáveis para armazenar os valores dos eventos
  long long values[NUM_EVENTS];

  // Cria um EventSet
  int EventSet = PAPI_NULL;
  if (PAPI_create_eventset(&EventSet) != PAPI_OK)
  {
    fprintf(stderr, "Erro ao criar EventSet.\n");
    exit(1);
  }

  // Verificar se PAPI_FP_OPS é suportado
  if (PAPI_query_event(PAPI_FP_OPS) == PAPI_OK)
  {
    // Se suportado, adicioná-lo ao EventSet
    if (PAPI_add_events(EventSet, events, num_events) != PAPI_OK)
    {
      fprintf(stderr, "Erro ao adicionar eventos ao EventSet.\n");
      exit(1);
    }
  }
  else
  {
    // Se não suportado, usar os outros eventos
    if (PAPI_add_events(EventSet, events, num_events - 1) != PAPI_OK)
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
  long long start_time = PAPI_get_real_usec();

  // Executa a função de teste
  test_function();

  // Registra o tempo de término
  long long end_time = PAPI_get_real_usec();

  // Para a contagem dos eventos e obtém os valores
  if (PAPI_stop(EventSet, values) != PAPI_OK)
  {
    fprintf(stderr, "Erro ao parar a contagem dos eventos.\n");
    exit(1);
  }

  // Calcula o tempo de execução real em segundos
  double real_time = (double)(end_time - start_time) / 1000000.0;

  // Exibe os resultados
  printf("-------------------------\n");
  printf("Resultados da Contagem PAPI:\n");
  printf("-------------------------\n");

  printf("Tempo de execução: %.6f segundos\n", real_time);

  // Imprime os valores de cada evento
  char event_name[PAPI_MAX_STR_LEN]; // Array para armazenar o nome do evento
  for (int i = 0; i < NUM_EVENTS; i++)
  {
    PAPI_event_code_to_name(events[i], event_name); // Obtem o nome do evento
    printf("%s: %lld\n", event_name, values[i]);
  }

  // Calcula e imprime o CPI (Instruções por Ciclo)
  double cpi = (double)values[3] / (double)values[4];
  printf("CPI: %.2f\n", cpi);

  // Libera o EventSet
  PAPI_cleanup_eventset(EventSet);

  return 0;
}