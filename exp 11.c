#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunction(LPVOID arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    DWORD threadId1, threadId2;

    char* message1 = "Hello from Thread 1!";
    char* message2 = "Hello from Thread 2!";

    // Create threads
    thread1 = CreateThread(NULL, 0, threadFunction, message1, 0, &threadId1);
    thread2 = CreateThread(NULL, 0, threadFunction, message2, 0, &threadId2);

    // Wait for threads to finish
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Close thread handles
    CloseHandle(thread1);
    CloseHandle(thread2);

    system("pause"); // keep console open
    return 0;
}
