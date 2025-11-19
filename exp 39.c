#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define DISK_END 199   // you can change disk size here

int main() {
    int n, head, seek_time = 0;
    int request_queue[MAX];
    int i, j;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request queue:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    // Sort the queue
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // Find the first request >= head
    int index = 0;
    for (i = 0; i < n; i++) {
        if (request_queue[i] >= head) {
            index = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    // Move RIGHT servicing requests >= head
    for (i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // Go to end of disk
    if (head != DISK_END) {
        seek_time += abs(DISK_END - head);
        head = DISK_END;
        printf(" -> %d", head);
    }

    // Jump to beginning (0)
    seek_time += DISK_END;  // DISK_END - 0
    head = 0;
    printf(" -> %d", head);

    // Move RIGHT servicing requests < original head
    for (i = 0; i < index; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}
