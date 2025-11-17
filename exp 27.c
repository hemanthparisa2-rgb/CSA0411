#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char filename[100], pattern[100], line[500];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        system("pause");   // prevent closing
        return 1;
    }

    printf("\n--- Lines containing '%s' ---\n", pattern);

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, pattern)) {  
            printf("%s", line);
        }
    }

    fclose(fp);

    system("pause");  // ? keeps the output window open
    return 0;
}
