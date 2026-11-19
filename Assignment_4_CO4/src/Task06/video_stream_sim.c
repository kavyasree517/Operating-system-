#include <stdio.h>
#include <stdlib.h>
#define NUM_REQUESTS 10000

int main(void) {
    unsigned int seed = 202604U;
    double sum_A = 0.0, max_A = 0.0, sum_B = 0.0, max_B = 0.0;
    long reads_A = 0, reads_B = 0;
    int head_B = 100;
    for (int i = 0; i < NUM_REQUESTS; i++) {
        seed = seed * 1103515245U + 12345U;
        int is_hot = ((seed % 100) < 85);
        int is_ram = ((seed / 100) % 100 < 20);
        int cyl = (int)((seed >> 16) % 200);
        double lat_a = is_ram ? 0.15 : (is_hot ? (reads_A++, 1.20 + (cyl % 5) * 0.15)
                                               : (reads_A++, 11.50 + (cyl % 15) * 0.45));
        sum_A += lat_a; if (lat_a > max_A) max_A = lat_a;
        reads_B += 3;
        int dist = abs(cyl - head_B); head_B = cyl;
        double lat_b = 18.0 + dist * 0.75 + (i % 12) * 8.5;
        sum_B += lat_b; if (lat_b > max_B) max_B = lat_b;
    }
    printf("Design A (Hybrid NVMe+XFS): reads=%ld, avg=%.2f ms, max=%.2f ms\n", reads_A, sum_A / NUM_REQUESTS, max_A);
    printf("Design B (All-HDD FCFS)   : reads=%ld, avg=%.2f ms, max=%.2f ms\n", reads_B, sum_B / NUM_REQUESTS, max_B);
    return 0;
}
