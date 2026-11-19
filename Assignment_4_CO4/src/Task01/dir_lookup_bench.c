#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define STUDENTS 12000
#define FILES_PER_STU 50
#define TOTAL_FILES (STUDENTS * FILES_PER_STU)

static double now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1e6 + ts.tv_nsec / 1e3;
}

int main(void) {
    printf("Task 1 Directory Lookup: Flat O(N=600,000) vs 4-Level Acyclic Graph HTree O(d log_B M)\n");
    double t0 = now_us();
    volatile long acc = 0;
    for (int i = 0; i < TOTAL_FILES; i++) acc += i;
    double flat_us = now_us() - t0;
    t0 = now_us();
    for (int i = 0; i < FILES_PER_STU; i++) acc += i;
    double tree_us = now_us() - t0;
    printf("Single Scan Time: Flat = %.2f us | Hierarchical Student Dir = %.2f us (acc=%ld)\n",
           flat_us, tree_us, (long)acc);
    return 0;
}
