#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred during fork
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello from Child! My PID is %d\n", getpid());
    } else {
        // Parent process
        printf("Hello from Parent! My PID is %d\n", getpid());
        printf("Parent: Created a Child with PID %d\n", pid);
    }

    return 0;
}