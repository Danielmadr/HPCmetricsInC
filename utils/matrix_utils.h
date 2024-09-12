#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

double **allocate_matrix(int N);
void free_matrix(double **matrix, int N);
void initialize_matrix(double **matrix, int N);
void print_matrix(double **matrix, int N);
void reset_matrix(double **matrix, int N);
int compare_matrices(double **A, double **B, int N);

#endif
