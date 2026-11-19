#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>

#define NUM_CAMERAS 64
#define WORK_PER_FRAME 500000

static atomic_int next_cam_idx = 0;
static long safe_plates_found = 0;
static long unsafe_counter = 0;
static pthread_mutex_t plate_lock = PTHREAD_MUTEX_INITIALIZER;

static int process_camera_frame(int cam_id) {
    unsigned int hash = (unsigned int)(cam_id + 1) * 2654435761u;
    for (int i = 0; i < WORK_PER_FRAME; i++)
        hash = (hash ^ (hash >> 15)) * 0x85ebca6bu + (unsigned int)i;
    return (hash != 0) ? 1 : 1;
}

static void *pool_worker(void *arg) {
    (void)arg;
    while (1) {
        int cam = atomic_fetch_add(&next_cam_idx, 1);
        if (cam >= NUM_CAMERAS) break;
        int found = process_camera_frame(cam);
        pthread_mutex_lock(&plate_lock);
        safe_plates_found += found;
        pthread_mutex_unlock(&plate_lock);
    }
    return NULL;
}

static double run_pool_benchmark(int num_threads) {
    struct timespec t0, t1;
    atomic_store(&next_cam_idx, 0);
    safe_plates_found = 0;
    pthread_t th[64];
    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i = 0; i < num_threads; i++) pthread_create(&th[i], NULL, pool_worker, NULL);
    for (int i = 0; i < num_threads; i++) pthread_join(th[i], NULL);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return (t1.tv_sec - t0.tv_sec) * 1000.0 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

static void *race_worker(void *arg) {
    (void)arg;
    for (int i = 0; i < 200000; i++) unsafe_counter++;
    return NULL;
}

int main(void) {
    int pools[] = {1, 4, 8, 16, 64};
    double t_base = 0.0;
    for (int i = 0; i < 5; i++) {
        double ms = run_pool_benchmark(pools[i]);
        if (i == 0) t_base = ms;
        printf("Pool %-2d threads: %7.2f ms (Speedup %.2fx, Plates=%ld)\n",
               pools[i], ms, t_base / ms, safe_plates_found);
    }
    pthread_t r1, r2;
    pthread_create(&r1, NULL, race_worker, NULL);
    pthread_create(&r2, NULL, race_worker, NULL);
    pthread_join(r1, NULL); pthread_join(r2, NULL);
    printf("Unprotected Counter Race: Expected=400000, Actual=%ld\n", unsafe_counter);
    return 0;
}
