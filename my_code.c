#include <stdio.h>
#include <time.h>

int main() {
    float a = 0.5, b = 2.5, c;
    int i;
    int num_operations = 1000000;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (i = 0; i < num_operations; i++) {
        c = a * b;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    double mflops = (num_operations / cpu_time_used) / 1000000;
    printf("MFLOPS: %f\n", mflops);

    return 0;
}
