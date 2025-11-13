#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int is_safe();

// Global data
int available[MAX_RESOURCES] = {3, 3, 2};
int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

int request_resources(int process_num, int request[]) {
    int i;
    // Check request validity
    for (i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > available[i] || request[i] > (maximum[process_num][i] - allocation[process_num][i])) {
            return 0;
        }
    }

    // Try allocation
    for (i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_num][i] += request[i];
    }

    if (is_safe()) {
        return 1;
    } else {
        for (i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_num][i] -= request[i];
        }
        return 0;
    }
}

int is_safe() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int i, j, k, count = 0, found;

    for (i = 0; i < MAX_RESOURCES; i++)
        work[i] = available[i];

    while (count < MAX_PROCESSES) {
        found = 0;
        for (i = 0; i < MAX_PROCESSES; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (maximum[i][j] - allocation[i][j] > work[j])
                        break;
                }
                if (j == MAX_RESOURCES) {
                    for (k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocation[i][k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found)
            return 0;
    }
    return 1;
}

int main() {
    int process_num;
    int request[MAX_RESOURCES];
    int i;

    printf("Enter process number (0 to 4): ");
    scanf("%d", &process_num);

    printf("Enter resource request (e.g., 0 1 0): ");
    for (i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &request[i]);

    if (request_resources(process_num, request)) {
        printf("\n? Request granted. System remains in a safe state.\n");
    } else {
        printf("\n? Request denied. System would enter an unsafe state.\n");
    }

    printf("\nPress any key to exit...");
    getchar();
    getchar();
    return 0;
}
