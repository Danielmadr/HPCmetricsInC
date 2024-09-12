#ifndef REPORT_UTILS_H
#define REPORT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "papi.h"


void report_header(FILE *report);

void report_info(FILE *report, int matrix_size);

void report_method(FILE *report, char *method);

void report_body(FILE *report, int events[], int num_events, char *method, long long *results, double *time);

void report_general_results(FILE *report, char *method, long long *results, double min_time, char *method_w_block, long long *results_w_block, double min_time_w_block, char *method_strassen, long long *results_strassen, double min_time_strassen, char *method_cblas, long long *results_cblas, double min_time_cblas);

#endif // REPORT_UTILS_H
