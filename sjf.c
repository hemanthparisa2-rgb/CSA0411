#include <stdio.h>
#include <stdlib.h>
int main()
{
    int at[10], bt[10], pr[10];
    int n, i, j, temp, time = 0, count, over = 0;
    int sum_wait = 0, sum_turnaround = 0, start;
    float avgwait, avgturn;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("\nEnter Arrival Time and Burst Time for Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        pr[i] = i + 1;
    }

    // Sort according to arrival time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                temp = at[i]; at[i] = at[j]; at[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
            }
        }
    }

    printf("\n\nProcess\t| Arrival\t| Burst\t| Start\t| End\t| Waiting\t| Turnaround\n");
    printf("--------------------------------------------------------------------------\n");

    while (over < n)
    {
        count = 0;

        // Count how many processes have arrived
        for (i = over; i < n; i++)
        {
            if (at[i] <= time)
                count++;
            else
                break;
        }

        // If more than one has arrived, sort that range by burst time
        if (count > 1)
        {
            for (i = over; i < over + count - 1; i++)
            {
                for (j = i + 1; j < over + count; j++)
                {
                    if (bt[i] > bt[j])
                    {
                        temp = at[i]; at[i] = at[j]; at[j] = temp;
                        temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                        temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                    }
                }
            }
        }

        // If no process has arrived yet, jump to next arrival
        if (at[over] > time)
            time = at[over];

        start = time;
        time += bt[over];

        printf("P[%d]\t| %d\t\t| %d\t| %d\t| %d\t| %d\t\t| %d\n",
               pr[over], at[over], bt[over], start, time,
               time - at[over] - bt[over], time - at[over]);

        sum_wait += time - at[over] - bt[over];
        sum_turnaround += time - at[over];
        over++;
    }

    avgwait = (float)sum_wait / n;
    avgturn = (float)sum_turnaround / n;

    printf("\nAverage Waiting Time: %.2f", avgwait);
    printf("\nAverage Turnaround Time: %.2f\n", avgturn);
    system("pause");
    return 0;
}
