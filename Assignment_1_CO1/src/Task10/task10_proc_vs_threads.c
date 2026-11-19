#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000

static void *thread_worker(void *arg) {
    (void)arg;
    return NULL;
}

static double elapsed_ms(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000.0 + (b.tv_nsec - a.tv_nsec) / 1e6;
}

int main(void) {
    struct timespec t0, t1;
    struct rusage ru_after;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i = 0; i < COUNT; i++) {
        pid_t pid = fork();
        if (pid == 0) _exit(0);
        waitpid(pid, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    getrusage(RUSAGE_SELF, &ru_after);
    printf("1000 Processes (fork+waitpid): %.2f ms (Max RSS: %ld KB)\n",
           elapsed_ms(t0, t1), ru_after.ru_maxrss);

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i = 0; i < COUNT; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_worker, NULL);
        pthread_join(tid, NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    getrusage(RUSAGE_SELF, &ru_after);
    printf("1000 Threads (pthread_create+join): %.2f ms (Max RSS: %ld KB)\n",
           elapsed_ms(t0, t1), ru_after.ru_maxrss);
    return 0;
}
