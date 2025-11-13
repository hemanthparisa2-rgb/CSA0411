#include <stdio.h>
#include <windows.h>

HANDLE mutex, writeBlock;
int data = 0, readersCount = 0;

DWORD WINAPI reader(LPVOID arg) {
    int i;
    for (i = 0; i < 10; i++) {
        WaitForSingleObject(mutex, INFINITE);
        readersCount++;
        if (readersCount == 1)
            WaitForSingleObject(writeBlock, INFINITE);
        ReleaseMutex(mutex);

        printf("Reader reads data: %d\n", data);
        Sleep(500);

        WaitForSingleObject(mutex, INFINITE);
        readersCount--;
        if (readersCount == 0)
            ReleaseSemaphore(writeBlock, 1, NULL);
        ReleaseMutex(mutex);
        Sleep(500);
    }
    return 0;
}

DWORD WINAPI writer(LPVOID arg) {
    int i;
    for (i = 0; i < 10; i++) {
        WaitForSingleObject(writeBlock, INFINITE);
        data++;
        printf("Writer writes data: %d\n", data);
        Sleep(500);
        ReleaseSemaphore(writeBlock, 1, NULL);
        Sleep(500);
    }
    return 0;
}

int main() {
    HANDLE readerThread, writerThread;

    mutex = CreateMutex(NULL, FALSE, NULL);
    writeBlock = CreateSemaphore(NULL, 1, 1, NULL);

    readerThread = CreateThread(NULL, 0, reader, NULL, 0, NULL);
    writerThread = CreateThread(NULL, 0, writer, NULL, 0, NULL);

    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);

    CloseHandle(readerThread);
    CloseHandle(writerThread);
    CloseHandle(mutex);
    CloseHandle(writeBlock);

    printf("\nAll operations completed.\n");
    printf("Press Enter to exit...");
    getchar();
    return 0;
}
