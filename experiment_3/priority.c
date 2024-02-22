#include <stdio.h>

void f_priority(int pid[], int at[], int bt[], int wt[], int tat[], int priority[], int size) {
    int completion_time[size], remaining_time[size];
    int total_wt = 0, total_tat = 0;

    // Initialize remaining_time array with burst times
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
    }

    int current_time = 0;
    int completed = 0;

    printf("Process\tPriority\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");

    while (completed < size) {
        int highest_priority = -1;
        for (int i = 0; i < size; i++) {
            if (at[i] <= current_time && remaining_time[i] > 0) {
                if (highest_priority == -1 || priority[i] < priority[highest_priority]) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) {
            current_time++;
        } else {
            int process = highest_priority;
            current_time += bt[process];
            completion_time[process] = current_time;
            tat[process] = completion_time[process] - at[process];
            wt[process] = tat[process] - bt[process];
            total_wt += wt[process];
            total_tat += tat[process];
            remaining_time[process] = 0;
            completed++;

            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[process], priority[process], at[process], bt[process], completion_time[process], tat[process], wt[process]);
        }
    }

    float avg_wt = (float)total_wt / size;
    float avg_tat = (float)total_tat / size;

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
}

int main() {
    int pid[] = {0, 1, 2, 3, 4};
    int at[] = {2, 0, 1, 4, 3};
    int bt[] = {6, 4, 8, 3, 2};
    int wt[5], tat[5], priority[] = {0, 2, 4, 1, 3};
    int size = sizeof(pid) / sizeof(pid[0]);

    f_priority(pid, at, bt, wt, tat, priority, size);

    return 0;
}
