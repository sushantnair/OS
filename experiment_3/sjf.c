#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

void sjf(int pid[], int at[], int bt[], int wt[], int tat[], int size) {
    int remaining_time[size];
    int finish_time[size];
    bool completed[size];

    // Initialize arrays
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
        completed[i] = false;
    }

    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < size) {
        int min_index = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < size; i++) {
            if (!completed[i] && at[i] <= current_time && remaining_time[i] < min_bt) {
                min_index = i;
                min_bt = remaining_time[i];
            }
        }

        if (min_index == -1) {
            current_time++;
        } else {
            // Execute the process
            remaining_time[min_index]--;
            current_time++;

            if (remaining_time[min_index] == 0) {
                completed_processes++;
                completed[min_index] = true;
                finish_time[min_index] = current_time;

                // Calculate waiting time and turnaround time
                wt[min_index] = finish_time[min_index] - at[min_index] - bt[min_index];
                tat[min_index] = finish_time[min_index] - at[min_index];

                if (wt[min_index] < 0) {
                    wt[min_index] = 0;
                }
            }
        }
    }

    // Print the table
    printf("Job\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < size; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], finish_time[i], tat[i], wt[i]);
    }
}

int main() {
    int pid[] = {1, 2, 0, 4, 3};
    int at[] = {0, 1, 2, 3, 4};
    int bt[] = {4, 8, 6, 2, 3};
    int size = sizeof(pid) / sizeof(pid[0]);
    int wt[size], tat[size];
    sjf(pid, at, bt, wt, tat, size);

    return 0;
}
