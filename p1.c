#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        printf("Child process: PID=%d\n", getpid());
        execlp("/bin/ls", "ls", NULL);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), child_pid);
        wait(NULL);
        printf("Parent process exiting.\n");
    }
    return 0;
}
