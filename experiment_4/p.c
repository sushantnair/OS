#include <stdio.h>
#include <stdlib.h>

void priority(int pid[], int at[], int bt[], int wt[], int tat[], int p[], int size) {
    int remaining_time[size];
    int current_time = 0;
    int completed = 0;

    // Initialize the remaining time for each process
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
    }

    printf("Process\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n");

    while (completed < size) {
        int selected = -1;
        int highest_priority = 9999; // A large initial value

        for (int i = 0; i < size; i++) {
            if (at[i] <= current_time && remaining_time[i] > 0 && p[i] < highest_priority) {
                selected = i;
                highest_priority = p[i];
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            remaining_time[selected]--;
            current_time++;

            if (remaining_time[selected] == 0) {
                completed++;
                int finish_time = current_time;
                int turnaround_time = finish_time - at[selected];
                int waiting_time = turnaround_time - bt[selected];

                printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[selected], at[selected], bt[selected], p[selected], finish_time, turnaround_time, waiting_time);

                wt[selected] = waiting_time;
                tat[selected] = turnaround_time;
            }
        }
    }
}

int main() {
    int pid[] = {0, 1, 2, 3, 4};
    int at[] = {2, 0, 1, 4, 3};
    int bt[] = {6, 4, 8, 3, 2};
    int p[] = {0, 2, 4, 1, 3};
    int size = 5;
    int wt[size], tat[size];

    priority(pid, at, bt, wt, tat, p, size);

    return 0;
}
