#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_PATH "myfifo"

void writerProcess() {
    int fd;
    char buffer[] = "Hello, Reader!";
    // Create a FIFO (named pipe)
    mkfifo(FIFO_PATH, 0666);
    // Open the FIFO for writing
    fd = open(FIFO_PATH, O_WRONLY);
    if (fd == -1) {
        perror("Error opening FIFO for writing");
        exit(EXIT_FAILURE);
    }
    // Write data to the FIFO
    write(fd, buffer, sizeof(buffer));
    // Close the FIFO
    close(fd);
    // Remove the FIFO
    unlink(FIFO_PATH);
}

void readerProcess() {
    int fd;
    char buffer[50];
    // Wait for FIFO to be created (minimal sync using sleep)
    sleep(1);
    // Open the FIFO for reading
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        exit(EXIT_FAILURE);
    }
    // Read data from the FIFO
    read(fd, buffer, sizeof(buffer));
    // Display the read data
    printf("Reader Process: Received message - %s\n", buffer);
    // Close the FIFO
    close(fd);
}

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process (writer)
        writerProcess();
    } else {
        // Parent process (reader)
        readerProcess();
    }
    return 0;
}
