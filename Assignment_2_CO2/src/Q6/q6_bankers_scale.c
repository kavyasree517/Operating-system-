#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXN 1000
#define R 3

static int avail[R], maxm[MAXN][R], alloc[MAXN][R], seq[MAXN];

int is_safe_n(int n) {
    int work[R], finish[MAXN] = {0}, count = 0;
    memcpy(work, avail, sizeof(work));
    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (finish[p]) continue;
            int ok = 1;
            for (int r = 0; r < R; r++)
                if (maxm[p][r] - alloc[p][r] > work[r]) { ok = 0; break; }
            if (ok) {
                for (int r = 0; r < R; r++) work[r] += alloc[p][r];
                finish[p] = 1;
                seq[count++] = p;
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main(void) {
    int sizes[] = {10, 100, 1000};
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        for (int r = 0; r < R; r++) avail[r] = 1;
        for (int p = 0; p < n; p++) {
            int need_val = (n - 1 - p) + 1;
            for (int r = 0; r < R; r++) {
                alloc[p][r] = 1;
                maxm[p][r] = 1 + need_val;
            }
        }
        struct timespec t0, t1;
        clock_gettime(CLOCK_MONOTONIC, &t0);
        int safe = is_safe_n(n);
        clock_gettime(CLOCK_MONOTONIC, &t1);
        double us = (t1.tv_sec - t0.tv_sec) * 1e6 + (t1.tv_nsec - t0.tv_nsec) / 1e3;
        printf("n = %4d, m = %d -> safe = %d, time = %8.2f microseconds\n", n, R, safe, us);
    }
    return 0;
}
