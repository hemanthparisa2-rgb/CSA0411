#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char source[100], target[100];
    char c;

    printf("Enter the filename to open for reading: ");
    scanf("%s", source);

    fptr1 = fopen(source, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s for reading.\n", source);
        exit(1);
    }

    printf("Enter the filename to open for writing: ");
    scanf("%s", target);

    fptr2 = fopen(target, "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s for writing.\n", target);
        fclose(fptr1);
        exit(1);
    }

    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    printf("\nContents copied successfully from '%s' to '%s'\n", source, target);

    fclose(fptr1);
    fclose(fptr2);

    system("pause"); // ? Keeps the window open
    return 0;
}
