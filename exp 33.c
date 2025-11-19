#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n) { 
    int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    int i, j, k;

    for (i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    printf("Reference String: ");
    for (i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Page Replacement Order:\n");

    for (i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        for (j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            int optimalPage = -1;
            int farthestDistance = -1;

            printf("Page %d -> ", page);

            for (j = 0; j < MAX_FRAMES; j++) {
                int futureDistance = 0;
                int found = 0;

                for (k = i + 1; k < n; k++) {
                    if (referenceString[k] == frames[j]) {
                        found = 1;
                        break;
                    }
                    futureDistance++;
                }

                if (!found) {
                    futureDistance = 999;
                }

                if (futureDistance > farthestDistance) {
                    farthestDistance = futureDistance;
                    optimalPage = j;
                }
            }

            frames[optimalPage] = page;
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    printf("\nPress Enter to exit...");
    getchar();  
    getchar();  // for online compilers needing two enters

    return 0;
}
