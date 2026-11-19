#include <stdio.h>
#define MAXF 16

static int find(const int f[], int used, int page) {
    for (int i = 0; i < used; i++) if (f[i] == page) return i;
    return -1;
}

int fifo(const int ref[], int len, int frames) {
    int f[MAXF], used = 0, next = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        if (find(f, used, ref[i]) >= 0) continue;
        faults++;
        if (used < frames) f[used++] = ref[i];
        else { f[next] = ref[i]; next = (next + 1) % frames; }
    }
    return faults;
}

int lru(const int ref[], int len, int frames) {
    int f[MAXF], last[MAXF], used = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        int k = find(f, used, ref[i]);
        if (k >= 0) { last[k] = i; continue; }
        faults++;
        if (used < frames) { f[used] = ref[i]; last[used] = i; used++; }
        else {
            int oldest = 0;
            for (int j = 1; j < frames; j++) if (last[j] < last[oldest]) oldest = j;
            f[oldest] = ref[i]; last[oldest] = i;
        }
    }
    return faults;
}

int optimal(const int ref[], int len, int frames) {
    int f[MAXF], used = 0, faults = 0;
    for (int i = 0; i < len; i++) {
        if (find(f, used, ref[i]) >= 0) continue;
        faults++;
        if (used < frames) { f[used++] = ref[i]; continue; }
        int victim = 0, farthest = -1;
        for (int j = 0; j < frames; j++) {
            int next_use = len + 1;
            for (int m = i + 1; m < len; m++) if (ref[m] == f[j]) { next_use = m; break; }
            if (next_use > farthest) { farthest = next_use; victim = j; }
        }
        f[victim] = ref[i];
    }
    return faults;
}

int main(void) {
    int ref[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = (int)(sizeof(ref) / sizeof(ref[0]));
    for (int frames = 3; frames <= 4; frames++)
        printf("%d frames: FIFO %d, LRU %d, Optimal %d\n",
               frames, fifo(ref, n, frames), lru(ref, n, frames), optimal(ref, n, frames));
    int b[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    printf("Belady string, FIFO: 3 frames %d faults, 4 frames %d faults\n",
           fifo(b, 12, 3), fifo(b, 12, 4));
    return 0;
}
