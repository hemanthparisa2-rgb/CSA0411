#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    // Write to "shared memory" (a file)
    fp = fopen("shared_memory.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char message[] = "Hello, shared memory (simulated in file)!";
    fprintf(fp, "%s", message);
    fclose(fp);

    printf("Data written to simulated shared memory: %s\n", message);

    // Read back from the file
    fp = fopen("shared_memory.txt", "r");
    if (fp == NULL) {
        printf("Error reading file!\n");
        return 1;
    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    printf("Data read back: %s\n", buffer);

    system("pause");
    return 0;
}
