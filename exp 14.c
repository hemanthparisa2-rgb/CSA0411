#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

void copyFile() {
    const char *source_file = "C:\\Users\\heman\\OneDrive\\Desktop\\OS Lab\\sasi.txt";
    const char *destination_file = "C:\\Users\\heman\\OneDrive\\Desktop\\OS Lab\\sk.txt";

    int source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0) {
        printf("Error: Cannot open source file. (%s)\n", strerror(errno));
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0) {
        printf("Error: Cannot create destination file. (%s)\n", strerror(errno));
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            printf("Error: Write failed. (%s)\n", strerror(errno));
            break;
        }
    }

    close(source_fd);
    close(dest_fd);
    printf("File copied successfully.\n");
}

void createFile() {
    // Create folder if missing (via system command)
    system("mkdir \"C:\\Users\\heman\\OneDrive\\Desktop\\OS Lab\"");

    FILE *fp = fopen("C:\\Users\\heman\\OneDrive\\Desktop\\OS Lab\\sasi.txt", "w");
    if (fp == NULL) {
        printf("Error: Unable to create file. (%s)\n", strerror(errno));
        return;
    }

    fprintf(fp, "This is a new file created successfully.\n");
    fclose(fp);
    printf("File created successfully.\n");
}

void deleteFile() {
    if (remove("C:\\Users\\heman\\OneDrive\\Desktop\\OS Lab\\sasi.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("Error: Unable to delete file. (%s)\n", strerror(errno));
}

int main() {
    int n;
    printf("1. Create \t2. Copy \t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            createFile();
            break;
        case 2:
            copyFile();
            break;
        case 3:
            deleteFile();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    printf("\nPress any key to exit...");
    getchar(); // consume newline
    getchar(); // wait for input
    return 0;
}
