#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>

#define DIM 2048

static double now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

int main(void) {
    size_t bytes = (size_t)DIM * DIM * sizeof(int);
    int *mat = malloc(bytes);
    struct rusage r0, r1;
    getrusage(RUSAGE_SELF, &r0);
    double t0 = now_ms();
    long long s = 0;
    for (int r = 0; r < DIM; r++)
        for (int c = 0; c < DIM; c++) { mat[r * DIM + c] = r + c; s += mat[r * DIM + c]; }
    double dt_row = now_ms() - t0;
    getrusage(RUSAGE_SELF, &r1);
    printf("Row-Major: %.2f ms (minor_faults=%ld, sum=%lld)\n", dt_row, r1.ru_minflt - r0.ru_minflt, s);
    free(mat);
    return 0;
}
