# TESTA SE TODAS AS MATRIZES ESTÃO DANDO AS RESPOSTAS CORRETAS

## **Compile o test:**

bash
```
gcc -o test test.c ../src/mat_mult/matrix_multiply.c ../src/blocking/matrix_multiply_blocking.c ../src/cblas/matrix_multiply_blas.c ../src/strassen/matrix_multiply_strassen.c ../utils/matrix_utils.c ../utils/performance_utils.c -lblas -lpapi -lm
```

## **Execute o test:**

```bash
./test
````
