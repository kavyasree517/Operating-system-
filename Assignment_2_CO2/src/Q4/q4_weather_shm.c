#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct {
    sem_t slot_free, item_ready;
    int value, eof;
} shm_channel_t;

int main(void) {
    shm_channel_t *ch = mmap(NULL, sizeof(*ch), PROT_READ | PROT_WRITE,
                             MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(&ch->slot_free, 1, 1);
    sem_init(&ch->item_ready, 1, 0);
    ch->eof = 0;
    pid_t pid = fork();
    if (pid == 0) {
        int count = 0, sum = 0, max = 0;
        while (1) {
            sem_wait(&ch->item_ready);
            if (ch->eof) break;
            int r = ch->value;
            sem_post(&ch->slot_free);
            if (count == 0 || r > max) max = r;
            sum += r; count++;
        }
        printf("analyser (shm): %d readings, average %.1f, max %d\n",
               count, count ? (double)sum / count : 0.0, max);
        _exit(0);
    }
    int readings[] = {31, 33, 36, 34, 41, 38};
    for (int i = 0; i < 6; i++) {
        sem_wait(&ch->slot_free);
        ch->value = readings[i];
        sem_post(&ch->item_ready);
    }
    sem_wait(&ch->slot_free); ch->eof = 1; sem_post(&ch->item_ready);
    waitpid(pid, NULL, 0);
    printf("reader: done\n");
    munmap(ch, sizeof(*ch));
    return 0;
}
