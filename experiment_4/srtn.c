#include <stdio.h>
#include <stdbool.h>

void srtn(int pid[], int at[], int bt[], int wt[], int tat[], int size) {
    int remaining_time[size];
    bool completed[size];

    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
        completed[i] = false;
    }

    int current_time = 0;
    int completed_processes = 0;

    printf("Job\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");

    while (completed_processes < size) {
        int shortest_job = -1;
        int shortest_time = 9999; // A large number as initial value

        for (int i = 0; i < size; i++) {
            if (at[i] <= current_time && !completed[i] && remaining_time[i] < shortest_time) {
                shortest_job = i;
                shortest_time = remaining_time[i];
            }
        }

        if (shortest_job == -1) {
            current_time++;
        } else {
            remaining_time[shortest_job]--;

            if (remaining_time[shortest_job] == 0) {
                completed_processes++;
                int finish_time = current_time + 1;
                tat[shortest_job] = finish_time - at[shortest_job];
                wt[shortest_job] = tat[shortest_job] - bt[shortest_job];
                completed[shortest_job] = true;

                printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 'A' + pid[shortest_job], at[shortest_job], bt[shortest_job], finish_time, tat[shortest_job], wt[shortest_job]);
            }

            current_time++;
        }
    }
}

int main() {
    int pid[] = {0, 1, 2, 3, 4};
    int at[] = {2, 0, 1, 4, 3};
    int bt[] = {6, 4, 8, 3, 2};
    int wt[5];
    int tat[5];

    srtn(pid, at, bt, wt, tat, 5);

    return 0;
}
