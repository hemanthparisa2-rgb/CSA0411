#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void searchFile(const char *pattern, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        system("pause");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main()
{
    char pattern[100], filename[100];

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    printf("Enter file name: ");
    scanf("%s", filename);

    searchFile(pattern, filename);

    printf("\nSearch Completed.\n");
    system("pause"); // keep window open

    return 0;
}
