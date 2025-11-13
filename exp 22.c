#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];

// Initialize all memory as free (-1)
void initializeMemory() {
    int i;
    for (i = 0; i < MAX_MEMORY; i++) {
        memory[i] = -1;
    }
}

// Display memory layout
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
            printf("Free block: %d - %d (size %d)\n", i, j - 1, j - i);
            i = j - 1;
            found = 1;
        }
    }

    if (!found) {
        printf("No free memory available.\n");
    }
}

// Allocate memory using Best-Fit algorithm
void allocateMemory(int processId, int size) {
    int i, j;
    int start = -1, blockSize = 0;
    int bestStart = -1, bestSize = MAX_MEMORY + 1;

    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            start = i;
            blockSize = 0;
            while (i < MAX_MEMORY && memory[i] == -1) {
                blockSize++;
                i++;
            }
            // If block can fit and is smaller than current best
            if (blockSize >= size && blockSize < bestSize) {
                bestSize = blockSize;
                bestStart = start;
            }
        }
    }

    if (bestStart != -1) {
        for (i = bestStart; i < bestStart + size; i++) {
            memory[i] = processId;
        }
        printf("Allocated memory block %d - %d to Process %d (size %d)\n",
               bestStart, bestStart + size - 1, processId, size);
    } else {
        printf("Memory allocation failed for Process %d (not enough space).\n", processId);
    }
}

// Free memory of a process
void deallocateMemory(int processId) {
    int i, released = 0;
    for (i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = -1;
            released = 1;
        }
    }
    if (released)
        printf("Memory released by Process %d\n", processId);
    else
        printf("No memory found for Process %d\n", processId);
}

// Main program
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
    getchar();
    getchar();
    return 0;
}
