## Multiplicação de Matrizes: Comparação de Algoritmos

Este projeto implementa diferentes algoritmos de multiplicação de matrizes e compara seu desempenho. Os algoritmos implementados são:

* **Multiplicação Tradicional:** Implementações básicas de multiplicação de matrizes usando diferentes ordens de loops (ijk, ikj, jik, jki, kij, kji).
* **Multiplicação com Blocagem:** Divide a matriz em blocos e realiza multiplicações em cada bloco para melhorar o desempenho.
* **Algoritmo de Strassen:** Um algoritmo recursivo que divide e conquista para multiplicar matrizes, com um desempenho logarítmico para algumas dimensões da matriz.
* **CBLAS:**  Utiliza a biblioteca CBLAS para realizar multiplicação de matrizes, oferecendo uma implementação otimizada.

### Como executar o programa:

1. **Compile o código:**
   ```bash
➜  gcc main.c matrix_utils.c performance_utils.c matrix_multiply.c matrix_multiply_blas.c matrix_multiply_blocking.c matrix_multiply_strassen.c -o main -lcblas -lm
➜  gcc test.c matrix_utils.c matrix_multiply.c matrix_multiply_blas.c matrix_multiply_blocking.c matrix_multiply_strassen.c performance_utils.c -o test -lcblas -lm

# gcc -o PAPItest PAPItest.c -lpapi    
   ```
   
   ou 
   
   ```bash
   gcc main.c matrix_utils.c matrix_multiply.c matrix_multiply_blas.c matrix_multiply_blocking.c -o main -lcblas -lm
   ```
   
   Substitua `-lcblas` por `-llapack` se você estiver usando LAPACK. 
   
2. **Execute o programa:**
   ```bash
   ./main
   ```

### Saída:

O programa gerará um relatório chamado `matrix_multiply_report.txt` na pasta `report`. Este relatório conterá os resultados de todas as multiplicações de matrizes, incluindo o tempo de execução de cada método para cada tamanho de matriz, e o melhor algoritmo encontrado. 

### Detalhes do código:

* **`matrix_utils.c`:**  Funções auxiliares para alocar, liberar e inicializar matrizes.
* **`matrix_multiply.c`:** Implementações dos algoritmos de multiplicação de matrizes tradicionais.
* **`matrix_multiply_blocking.c`:** Implementação do algoritmo de multiplicação de matrizes com blocagem.
* **`matrix_multiply_strassen.c`:** Implementação do algoritmo de Strassen.
* **`matrix_multiply_blas.c`:** Implementação da multiplicação de matrizes usando CBLAS.

### Observações:

* O programa testa a multiplicação de matrizes quadradas de diferentes tamanhos, definidos no arquivo `main.c`. 
* O tamanho dos blocos para a multiplicação com blocagem também é definido no arquivo `main.c`. 
* Este projeto é um exemplo simples de como comparar o desempenho de diferentes algoritmos de multiplicação de matrizes. 
* Você pode modificar o código para adicionar novos algoritmos, testar matrizes de diferentes tamanhos e realizar outras análises de desempenho.

Espero que este código seja útil para você!
