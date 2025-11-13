#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];

// Initialize memory with -1 (unallocated)
void initializeMemory() {
    int i;
    for (i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1;
    }
}

// Display memory status
void displayMemory() {
    int i, j;
    int found = 0;

    printf("\nMemory Status:\n");
    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            j = i;
            while (j < MAX_MEMORY && memory[j] == -1) {
                j++;
            }
            printf("Free memory block: %d - %d\n", i, j - 1);
            i = j - 1;
            found = 1;
        }
    }

    if (!found) {
        printf("No free memory available.\n");
    }
}

// Allocate memory using *First Fit* (simplified)
void allocateMemory(int processId, int size) {
    int i, j, start = -1, count = 0;

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (start == -1) start = i;
            count++;
            if (count == size) {
                for (j = start; j < start + size; j++) {
                    memory[j] = processId;
                }
                printf("Allocated memory block %d - %d to Process %d\n",
                       start, start + size - 1, processId);
                return;
            }
        } else {
            start = -1;
            count = 0;
        }
    }

    printf("Memory allocation for Process %d failed (not enough contiguous memory).\n", processId);
}

// Deallocate memory for a process
void deallocateMemory(int processId) {
    int i;
    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
        }
    }
    printf("Memory released by Process %d\n", processId);
}

int main() {
    initializeMemory();
    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    printf("\nPress Enter to exit...");
    getchar(); getchar();
    return 0;
}
