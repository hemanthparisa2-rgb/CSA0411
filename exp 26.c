#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;

    // Create & Write to file
    file = fopen("example.txt", "w");
    if (file == NULL) {
        printf("Error opening the file for writing.\n");
        return 1;
    }

    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a C file management example.\n");
    fclose(file);

    // Read file
    file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening the file for reading.\n");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);

    system("pause"); // ?? keeps console open in Dev-C++
    return 0;
}
