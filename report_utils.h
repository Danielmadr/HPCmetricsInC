#ifndef REPORT_UTILS_H
#define REPORT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "papi.h"

// Função para gerar o cabeçalho do relatório
void report_header(FILE *report);

// Função para gerar o corpo do relatório
void report_body(FILE *report, int events[], int num_events, long long *results, char *method);

void report_info(FILE *report, int matrix_size, char *method, int num_blocks);

#endif // REPORT_UTILS_H
