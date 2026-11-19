#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static void show_proc_status(pid_t pid, const char *role) {
    char path[64], line[256];
    snprintf(path, sizeof(path), "/proc/%d/status", (int)pid);
    FILE *f = fopen(path, "r");
    if (!f) return;
    printf("--- /proc/%d/status [%s] ---\n", (int)pid, role);
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Name:", 5) == 0 || strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "Pid:", 4) == 0  || strncmp(line, "PPid:", 5) == 0  ||
            strncmp(line, "VmRSS:", 6) == 0 || strncmp(line, "VmPTE:", 6) == 0 ||
            strstr(line, "ctxt_switches") != NULL) {
            fputs("  ", stdout);
            fputs(line, stdout);
        }
    }
    fclose(f);
}

int main(void) {
    printf("Exam Server Master PID: %d\n", (int)getpid());
    fflush(stdout);
    pid_t pid_session = fork();
    if (pid_session == 0) { sleep(1); _exit(0); }
    pid_t pid_autosave = fork();
    if (pid_autosave == 0) { sleep(1); _exit(0); }
    pid_t pid_proctor = fork();
    if (pid_proctor == 0) { _exit(0); }
    usleep(100000);
    show_proc_status(pid_session, "Student-Session (WAITING/Sleeping)");
    show_proc_status(pid_proctor, "Video-Proctor (TERMINATED/Zombie)");
    while (waitpid(-1, NULL, 0) > 0);
    printf("All child processes reaped cleanly.\n");
    return 0;
}
