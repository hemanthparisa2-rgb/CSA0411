#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5
HANDLE chopsticks[NUM_PHILOSOPHERS];

DWORD WINAPI philosopherLifeCycle(LPVOID arg) {
    int id = *((int*)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        Sleep((rand() % 3 + 1) * 1000); // thinking time

        WaitForSingleObject(chopsticks[left_chopstick], INFINITE);
        WaitForSingleObject(chopsticks[right_chopstick], INFINITE);

        printf("Philosopher %d is eating...\n", id);
        Sleep((rand() % 3 + 1) * 1000); // eating time

        ReleaseMutex(chopsticks[left_chopstick]);
        ReleaseMutex(chopsticks[right_chopstick]);
    }

    return 0;
}

int main() {
    HANDLE philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    int i; // ? Declare outside

    // Initialize mutexes
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        chopsticks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    // Create threads
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        philosophers[i] = CreateThread(NULL, 0, philosopherLifeCycle, &philosopher_ids[i], 0, NULL);
    }

    // Wait indefinitely
    WaitForMultipleObjects(NUM_PHILOSOPHERS, philosophers, TRUE, INFINITE);

    // Cleanup
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        CloseHandle(chopsticks[i]);
    }

    system("pause");
    return 0;
}
