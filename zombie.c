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
        printf("Child process (Zombie) with PID: %d\n", getpid());
        exit(0); // Child process exits
    } else {
        // Parent process
        printf("Parent process with PID: %d\n", getpid());
        sleep(10); // Sleep to keep the child process in zombie state
        printf("Parent process finished sleeping\n");

        // Reaping the zombie process
        wait(NULL);
        printf("Child process reaped\n");
    }

    return 0;
}
