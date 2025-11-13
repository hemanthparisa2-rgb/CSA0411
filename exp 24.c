#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[100];

    // Creating a new file
    fd = creat("sample.txt", S_IRWXU);  // rwx------ (read, write, execute for user)
    if (fd == -1) {
        perror("create");
        exit(1);
    } else {
        printf("File 'sample.txt' created successfully.\n");
        close(fd);
    }

    // Opening the existing file for writing
    fd = open("sample.txt", O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for writing.\n");
    }

    // Writing data to the file
    if (write(fd, "Hello, World!\n", 14) == -1) {
        perror("write");
        exit(1);
    } else {
        printf("Data written to 'sample.txt'.\n");
    }
    close(fd);

    // Opening the file for reading
    fd = open("sample.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    } else {
        printf("File 'sample.txt' opened for reading.\n");
    }

    // Reading data from the file
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    } else {
        buffer[bytesRead] = '\0'; // Null-terminate string
        printf("Data read from 'sample.txt':\n%s", buffer);
    }
    close(fd);

    // Deleting the file
    if (remove("sample.txt") == -1) {
        perror("remove");
        exit(1);
    } else {
        printf("File 'sample.txt' deleted successfully.\n");
    }

    return 0;
}
