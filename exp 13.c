#include <stdio.h>

// Function to sort in ascending order
void sort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Function to sort in descending order
void rsort(int a[], int n) {
    int i, j, t;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Best Fit logic (used for all)
void bestfit(int mp[], int p[], int m, int n) {
    int i, j = 0;

    for (i = 0; i < n && j < m; i++) {
        if (mp[i] >= p[j]) {
            printf("\nProcess %d (size %d) fits in partition %d (size %d)",
                   j + 1, p[j], i + 1, mp[i]);
            mp[i] = mp[i] - p[j];
            j++;
            i = -1; // Restart checking from first partition
        }
    }

    for (; j < m; j++) {
        printf("\nProcess %d (size %d) must wait — not enough memory", j + 1, p[j]);
    }
}

// First Fit strategy (sort ascending)
void firstfit(int mp[], int p[], int m, int n) {
    sort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

// Worst Fit strategy (sort descending)
void worstfit(int mp[], int p[], int m, int n) {
    rsort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

int main() {
    int m, n, mp[20], p[20], ch, i;

    printf("Number of memory partitions: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter the memory partitions:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }

    printf("Enter process sizes:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
        printf("\n--- FIRST FIT ---\n");
        firstfit(mp, p, m, n);
        break;

    case 2:
        printf("\n--- BEST FIT ---\n");
        bestfit(mp, p, m, n);
        break;

    case 3:
        printf("\n--- WORST FIT ---\n");
        worstfit(mp, p, m, n);
        break;

    default:
        printf("Invalid choice!\n");
        break;
    }

    printf("\n");
    system("pause"); // Keeps the output open in Dev-C++
    return 0;
}
