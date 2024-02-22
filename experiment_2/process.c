#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h> // Include this header for wait()

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // This code is executed by the child process

        printf("Child Process Details:\n");
        printf("PID: %d\n", getpid());  // Get the child process ID
        printf("Parent's PID (PPID): %d\n", getppid());  // Get the parent process ID

        // Open and read a file in the child process
        int fd = open("sample.txt", O_RDONLY);
        if (fd < 0) {
            perror("Failed to open the file");
            exit(1);
        }

        char buffer[1024];
        ssize_t n;

        while ((n = read(fd, buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, n);  // Display file contents to the standard output
        }

        close(fd);
    } else {
        // This code is executed by the parent process

        printf("Parent Process Details:\n");
        printf("PID: %d\n", getpid());  // Get the parent process ID
        printf("Child's PID: %d\n", pid);  // Get the child process ID

        // Wait for the child process to finish
        wait(NULL);

        printf("Child process has finished.\n");
    }

    return 0;
}
