#include <stdio.h>

int main()
{
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0;
    int at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    printf("Enter total number of processes: ");
    scanf("%d", &NOP);
    y = NOP; // Number of processes left

    for (i = 0; i < NOP; i++)
    {
        printf("\nEnter the Arrival Time and Burst Time for Process[%d]\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    printf("\nEnter the Time Quantum: ");
    scanf("%d", &quant);

    printf("\nProcess\t\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }

        if (temp[i] == 0 && count == 1)
        {
            y--;
            printf("P[%d]\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }

        if (i == NOP - 1)
            i = 0;
        else if (at[i + 1] <= sum)
            i++;
        else
            i = 0;
    }

    avg_wt = (float)wt / NOP;
    avg_tat = (float)tat / NOP;

    printf("\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
