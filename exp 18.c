/* producer_consumer_win.c
   Windows (Dev-C++) version using WinAPI semaphores & threads.
   Pure C (C89 compatible).
*/

#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

/* buffer and indices */
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

/* counters */
int produced_items = 0;
int consumed_items = 0;

/* WinAPI synchronization objects */
HANDLE semEmpty;   /* counts empty slots */
HANDLE semFull;    /* counts filled slots */
HANDLE hMutex;     /* binary mutex to protect buffer */

DWORD WINAPI producer(LPVOID arg) {
    while (1) {
        /* stop condition */
        if (produced_items >= MAX_ITEMS) break;

        /* wait for an empty slot */
        WaitForSingleObject(semEmpty, INFINITE);

        /* enter critical section */
        WaitForSingleObject(hMutex, INFINITE);

        /* produce item into circular buffer */
        buffer[in] = produced_items + 1;
        printf("Produced: %d (slot %d)\n", buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        produced_items++;

        /* leave critical section */
        ReleaseMutex(hMutex);

        /* signal a filled slot */
        ReleaseSemaphore(semFull, 1, NULL);

        /* small sleep to make output readable */
        Sleep(200);
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID arg) {
    while (1) {
        /* stop condition */
        if (consumed_items >= MAX_ITEMS) break;

        /* wait for a filled slot */
        WaitForSingleObject(semFull, INFINITE);

        /* enter critical section */
        WaitForSingleObject(hMutex, INFINITE);

        /* consume item from circular buffer */
        {
            int item = buffer[out];
            printf("Consumed: %d (slot %d)\n", item, out);
            buffer[out] = 0; /* optional: clear slot */
            out = (out + 1) % BUFFER_SIZE;
            consumed_items++;
        }

        /* leave critical section */
        ReleaseMutex(hMutex);

        /* signal an empty slot */
        ReleaseSemaphore(semEmpty, 1, NULL);

        /* small sleep to make output readable */
        Sleep(300);
    }
    return 0;
}

int main(void) {
    DWORD prodId, consId;
    HANDLE prodThread, consThread;
    int i;

    /* initialize buffer */
    for (i = 0; i < BUFFER_SIZE; ++i) buffer[i] = 0;

    /* create semaphores:
       semEmpty starts with BUFFER_SIZE (all slots empty)
       semFull  starts with 0 (no filled slots)
    */
    semEmpty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    semFull  = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    if (!semEmpty || !semFull) {
        printf("Failed to create semaphores. Error: %lu\n", GetLastError());
        return 1;
    }

    /* create mutex */
    hMutex = CreateMutex(NULL, FALSE, NULL);
    if (!hMutex) {
        printf("Failed to create mutex. Error: %lu\n", GetLastError());
        CloseHandle(semEmpty);
        CloseHandle(semFull);
        return 1;
    }

    /* create producer and consumer threads */
    prodThread = CreateThread(NULL, 0, producer, NULL, 0, &prodId);
    consThread = CreateThread(NULL, 0, consumer, NULL, 0, &consId);
    if (!prodThread || !consThread) {
        printf("Failed to create threads. Error: %lu\n", GetLastError());
        CloseHandle(semEmpty);
        CloseHandle(semFull);
        CloseHandle(hMutex);
        return 1;
    }

    /* wait for threads to finish */
    WaitForSingleObject(prodThread, INFINITE);
    WaitForSingleObject(consThread, INFINITE);

    /* cleanup */
    CloseHandle(prodThread);
    CloseHandle(consThread);
    CloseHandle(semEmpty);
    CloseHandle(semFull);
    CloseHandle(hMutex);

    printf("\nAll items produced and consumed successfully.\n");
    printf("Press Enter to exit...");
    getchar(); /* pause */
    return 0;
}
