#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/mman.h>
#include <sys/resource.h>

#define RT_BUF_SIZE (4 * 1024 * 1024)
#define ITERATIONS 50

static uint64_t now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
}

static void bench(int use_mlock) {
    struct rusage r0, r1;
    uint8_t *buf = mmap(NULL, RT_BUF_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (use_mlock) { mlock(buf, RT_BUF_SIZE); memset(buf, 1, RT_BUF_SIZE); }
    getrusage(RUSAGE_SELF, &r0);
    uint64_t max_ns = 0;
    for (int it = 0; it < ITERATIONS; it++) {
        uint64_t t0 = now_ns();
        for (size_t off = 0; off < 64 * 4096; off += 4096) buf[(it * 4096 + off) % RT_BUF_SIZE] ^= (uint8_t)it;
        uint64_t dt = now_ns() - t0;
        if (dt > max_ns) max_ns = dt;
    }
    getrusage(RUSAGE_SELF, &r1);
    printf("[%s] Max Delay: %.2f us | Minor Faults: %ld\n",
           use_mlock ? "LOCKED" : "UNLOCKED", max_ns / 1000.0, r1.ru_minflt - r0.ru_minflt);
    munmap(buf, RT_BUF_SIZE);
}

int main(void) {
    bench(0);
    bench(1);
    return 0;
}
