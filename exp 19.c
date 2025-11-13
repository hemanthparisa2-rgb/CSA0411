#include <stdio.h>
#include <windows.h>

int counter = 0;          // Shared variable
HANDLE mutex;             // Mutex for synchronization

DWORD WINAPI threadFunction(LPVOID arg) {
    int i;
    for (i = 0; i < 1000000; i++) {
        WaitForSingleObject(mutex, INFINITE); // Lock
        counter++;                            // Critical section
        ReleaseMutex(mutex);                  // Unlock
    }
    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // Create mutex
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        printf("Failed to create mutex.\n");
        return 1;
    }

    // Create two threads
    thread1 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

    if (thread1 == NULL || thread2 == NULL) {
        printf("Failed to create threads.\n");
        return 1;
    }

    // Wait for threads to complete
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread and mutex handles
    CloseHandle(thread1);
    CloseHandle(thread2);
    CloseHandle(mutex);

    // Print final counter value
    printf("Final counter value: %d\n", counter);

    // Keep window open
    printf("Press Enter to exit...");
    getchar();
    return 0;
}
