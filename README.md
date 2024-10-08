## Multiplicação de Matrizes: Comparação de Algoritmos

Este projeto implementa diferentes algoritmos de multiplicação de matrizes e compara seu desempenho. Os algoritmos implementados são:

- **Multiplicação Tradicional:** Implementações básicas de multiplicação de matrizes usando diferentes ordens de loops (ijk, ikj, jik, jki, kij, kji).
- **Multiplicação com Blocagem:** Divide a matriz em blocos e realiza multiplicações em cada bloco para melhorar o desempenho.
- **Algoritmo de Strassen:** Um algoritmo recursivo que divide e conquista para multiplicar matrizes, com um desempenho logarítmico para algumas dimensões da matriz.
- **CBLAS:** Utiliza a biblioteca CBLAS para realizar multiplicação de matrizes, oferecendo uma implementação otimizada.

### Instalação

**Pré-requisitos:**

- Compilador C (gcc ou clang)
- Biblioteca CBLAS (geralmente incluída em distribuições Linux)
- Biblioteca PAPI (para medições de desempenho)

**Instalação da Biblioteca PAPI**

1. **Baixe o código-fonte da PAPI:**

   ```bash
   git clone https://github.com/PAPI/PAPI.git
   ```

2. **Configure, compile e instale a PAPI:**
   ```bash
   cd PAPI
   ./configure
   make
   make test
   sudo make install
   ```

**Instalação da Biblioteca CBLAS (se necessário)**

A maioria das distribuições Linux inclui a biblioteca CBLAS (geralmente como parte do pacote LAPACK). Se você não a tiver instalada, verifique o repositório de pacotes da sua distribuição para obter instruções de instalação.

**Compilação do Projeto**

1. **Navegue para o diretório do projeto:**

   ```bash
   cd matrix-multiplication
   ```

2. **Compile o programa:**
   ```bash
   gcc main.c ../utils/matrix_utils.c ../utils/performance_utils.c mat_mult/matrix_multiply.c cblas/matrix_multiply_blas.c blocking/matrix_multiply_blocking.c strassen/matrix_multiply_strassen.c ../utils/report_utils.c -o main -lcblas -lpapi -lm
   ```

Substitua `-lcblas` por `-llapack` se você estiver usando LAPACK.

### Como executar o programa:

1. **Execute o programa:**
   ```bash
   ./main
   ```

### Saída:

O programa gerará um relatório chamado `matrix_multiply_report.txt` na pasta `report`. Este relatório conterá os resultados de todas as multiplicações de matrizes, incluindo o tempo de execução de cada método para cada tamanho de matriz, e o melhor algoritmo encontrado.

### Detalhes do código:

- **`matrix_utils.c`:** Funções auxiliares para alocar, liberar e inicializar matrizes.
- **`matrix_multiply.c`:** Implementações dos algoritmos de multiplicação de matrizes tradicionais.
- **`matrix_multiply_blocking.c`:** Implementação do algoritmo de multiplicação de matrizes com blocagem.
- **`matrix_multiply_strassen.c`:** Implementação do algoritmo de Strassen.
- **`matrix_multiply_blas.c`:** Implementação da multiplicação de matrizes usando CBLAS.

### Observações:

- O programa testa a multiplicação de matrizes quadradas de diferentes tamanhos, definidos no arquivo `main.c`.
- O tamanho dos blocos para a multiplicação com blocagem também é definido no arquivo `main.c`.
- Este projeto é um exemplo simples de como comparar o desempenho de diferentes algoritmos de multiplicação de matrizes.
- Você pode modificar o código para adicionar novos algoritmos, testar matrizes de diferentes tamanhos e realizar outras análises de desempenho.

gcc test.c matrix_utils.c matrix_multiply.c matrix_multiply_blas.c matrix_multiply_blocking.c matrix_multiply_strassen.c performance_utils.c -o test -lcblas -lm

Espero que este código seja útil para você!
