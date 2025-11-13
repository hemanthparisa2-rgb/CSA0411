#include <stdio.h>
#include <stdlib.h>

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main() {
    int number_of_process;
    struct priority_scheduling temp_process;
    int total_waiting_time = 0, total_turnaround_time = 0;
    int position;
    float average_waiting_time, average_turnaround_time;
    int ASCII_number = 65; // To name processes as A, B, C...
    int i, j; // ? Declare loop variables here (before loops)

    printf("Enter the total number of processes: ");
    scanf("%d", &number_of_process);

    struct priority_scheduling process[number_of_process];

    printf("\nEnter the Burst Time and Priority of each process:\n");

    for (i = 0; i < number_of_process; i++) {
        process[i].process_name = (char)ASCII_number;
        printf("\nProcess %c\n", process[i].process_name);

        printf("Enter Burst Time: ");
        scanf("%d", &process[i].burst_time);

        printf("Enter Priority (Higher number = Higher priority): ");
        scanf("%d", &process[i].priority);

        ASCII_number++;
    }

    // Sort processes by priority (Descending)
    for (i = 0; i < number_of_process - 1; i++) {
        position = i;
        for (j = i + 1; j < number_of_process; j++) {
            if (process[j].priority > process[position].priority)
                position = j;
        }

        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // Calculate Waiting Time
    process[0].waiting_time = 0;
    for (i = 1; i < number_of_process; i++) {
        process[i].waiting_time = 0;
        for (j = 0; j < i; j++)
            process[i].waiting_time += process[j].burst_time;
        total_waiting_time += process[i].waiting_time;
    }

    average_waiting_time = (float)total_waiting_time / number_of_process;

    // Calculate Turnaround Time
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < number_of_process; i++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;
        total_turnaround_time += process[i].turn_around_time;

        printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i].process_name,
               process[i].burst_time,
               process[i].priority,
               process[i].waiting_time,
               process[i].turn_around_time);
    }

    average_turnaround_time = (float)total_turnaround_time / number_of_process;

    printf("\nAverage Waiting Time: %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    system("pause"); // Keeps output window open in Dev-C++
    return 0;
}
