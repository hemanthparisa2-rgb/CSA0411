#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char message[100];

    // Simulate Producer
    strcpy(message, "Hello, message queue (simulated)!");
    fp = fopen("msgqueue.txt", "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return 1;
    }
    fprintf(fp, "%s", message);
    fclose(fp);
    printf("Producer: Data sent ? %s\n", message);

    // Simulate Consumer
    fp = fopen("msgqueue.txt", "r");
    if (fp == NULL) {
        printf("Error reading file!\n");
        return 1;
    }
    char buffer[100];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);
    printf("Consumer: Data received ? %s\n", buffer);

    system("pause"); // keep window open
    return 0;
}
