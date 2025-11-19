#include <stdio.h>
#include <stdlib.h>

#define MAX 100

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

    // Sort request queue
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    printf("\nSCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    // Find index where head fits in sorted list
    int index = 0;
    for (i = 0; i < n; i++) {
        if (request_queue[i] >= head) {
            index = i;
            break;
        }
    }

    // Move right
    for (i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // Move to end of disk (simulate turning point)
    // Assuming disk size = 199
    int disk_end = 199;
    if (head != disk_end) {
        seek_time += abs(head - disk_end);
        head = disk_end;
        printf(" -> %d", head);
    }

    // Move left
    for (i = index - 1; i >= 0; i--) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}
