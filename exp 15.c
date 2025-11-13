#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char mainDirectory[] = "Hemanth - Personal";
    char subDirectory[] = "os";
    char fileName[] = "example.txt";
    char filePath[200];
    char mainDirPath[200];

    // Create directory path and full file path
    snprintf(mainDirPath, sizeof(mainDirPath), "%s/%s/", mainDirectory, subDirectory);
    snprintf(filePath, sizeof(filePath), "%s%s", mainDirPath, fileName);

    // Create and write to the file
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        printf("\nPress any key to exit...");
        getchar();
        return 1;
    }

    fprintf(file, "This is an example file content.");
    fclose(file);

    printf("File created successfully: %s\n", filePath);

    // Keep console open in Dev C++
    printf("\nPress any key to exit...");
    getchar(); // waits for Enter key
    return 0;
}
