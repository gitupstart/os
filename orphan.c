#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(2); // Ensure the parent exits before the child
        printf("Orphan child process with PID: %d, new PPID: %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("Parent process with PID: %d\n", getpid());
        printf("Parent process exiting\n");
        exit(0); // Parent exits
    }

    return 0;
}

