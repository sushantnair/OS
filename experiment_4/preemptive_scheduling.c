#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void srtn(int pid[], int at[], int bt[], int wt[], int tat[], int size)
{
    printf("\n-------------------------------------------------------------------------------");
    printf("\nInside SRTN function...");
    printf("\n-------------------------------------------------------------------------------");
    printf("\nPrinting data...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n-------------------------------------------------------------------------------");
    printf("\nForming table...");
    int remaining_time[size];
    bool completed[size];
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
        completed[i] = false;
    }
    int current_time = 0;
    int completed_processes = 0;
    printf("\nJob\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
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
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");   
}

void rr(int pid[], int at[], int bt[], int size, int quantum)
{
    //pid is analogous to Array1; bt is analogous to Array2; wt is analogous to Array3
    printf("\n-------------------------------------------------------------------------------");
    printf("\nInside RR function...");
    printf("\n-------------------------------------------------------------------------------");
    printf("\nPrinting data...");
    printf("\nProcess ID\tArrival Time\tBurst Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d", pid[i], at[i], bt[i]);
    }
    printf("\n-------------------------------------------------------------------------------\n");
    int remaining_time[size];
    int finish_time[size];
    int tat[size];
    int wt[size];
    int time = 0;
    int total_tat = 0;
    int total_wt = 0;
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
        finish_time[i] = 0;
        tat[i] = 0;
        wt[i] = 0;
    }
    int done = 0;
    while (!done) {
        done = 1;
        for (int i = 0; i < size; i++) {
            if (remaining_time[i] > 0) {
                done = 0;

                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    finish_time[i] = time;
                    tat[i] = finish_time[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    total_tat += tat[i];
                    total_wt += wt[i];
                    remaining_time[i] = 0;
                }
            }
        }
    }
    // Print the table
    printf("Job\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[i], at[i], bt[i], finish_time[i], tat[i], wt[i]);
    }
    // Calculate and print average turnaround time and waiting time
    float avg_tat = (float)total_tat / size;
    float avg_wt = (float)total_wt / size;
    printf("Average\t%.1f\t%.1f\n", avg_tat, avg_wt);
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");
}

void priority(int pid[], int at[], int bt[], int wt[], int tat[], int p[], int size)
{
    printf("\n-------------------------------------------------------------------------------");
    printf("\nInside Priority function...");
    printf("\n-------------------------------------------------------------------------------");
    printf("\nPrinting data...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n-------------------------------------------------------------------------------\n");\
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
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n-------------------------------------------------------------------------------");
}

int main() 
{
    printf("\n-------------------------------------------------------------------------------");
    printf("\n--------------------Preemptive Scheduling Algorithm Program--------------------");
    printf("\n-------------------------------------------------------------------------------");
    int ch_run;
    while(0 < 1){
        fflush(stdin);
        printf("\nEnter 1 for Shortest Remaining Time Next\nEnter 2 for Round Robin\nEnter 3 for Priority\nEnter choice: ");
        int ch_algo, n;
        scanf("%d", &ch_algo);
        printf("\n-----------------------------------------------------------------------------------");
        printf("\nEnter 1 for default values and 2 for custom values\nEnter choice: ");
        int ch_val;
        scanf("%d", &ch_val);
        if(ch_val == 1){
            n = 5;
            int pid[n], wt[n], tat[n];
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nEntered data: Choice = %d, Number of processes = %d", ch_algo, n);
            printf("\n-----------------------------------------------------------------------------------");
            //Initializing Process ID Array
            for(int i = 0; i < n; i++){
                pid[i] = i;
                printf("\nProcess %d has got Process ID %d.", i+1, pid[i]);
            }
            printf("\nProcess ID Array initialized successfully.");
            printf("\n-----------------------------------------------------------------------------------");
            int at[] = {2, 0, 1, 4, 3};
            for(int i = 0; i < n; i++)
                printf("\nProcess %d has got Arrival Time %d.", i+1, at[i]);
            printf("\n-----------------------------------------------------------------------------------");
            int bt[] = {6, 4, 8, 3, 2};
            for(int i = 0; i < n; i++)
                printf("\nProcess %d has got Burst Time %d.", i+1, bt[i]);
            int quantum;
            switch(ch_algo)
            {
                case 1:
                    printf("\nYou selected SRTN!");
                    srtn(pid, at, bt, wt, tat, n);
                    break;
                case 2:
                    printf("\nYou selected RR!");
                    printf("\nEnter time quantum: ");
                    scanf("%d", &quantum);
                    rr(pid, at, bt, n, quantum);
                    break;
                case 3:
                    printf("\nYou selected Priority!");
                    printf("\n-----------------------------------------------------------------------------------");
                    int p[] = {0, 2, 4, 1, 3};
                    for(int i = 0; i < n; i++)
                        printf("\nProcess %d has got Priority %d.", i+1, p[i]);
                    priority(pid, at, bt, wt, tat, p, n);
                    break;
                default:
                    printf("\nInvalid choice!");
            }
        } else {
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nEnter the number of processes in ready queue (arrival time of all processes is assumed to be 0 ms): ");
            scanf("%d", &n);
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nEntered data: Choice = %d, Number of processes = %d", ch_algo, n);
            printf("\n-----------------------------------------------------------------------------------");
            int pid[n], at[n], bt[n], wt[n], tat[n], p[n];
            //Initializing Process ID Array
            for(int i = 0; i < n; i++){
                pid[i] = i;
                printf("\nProcess %d has got Process ID %d.", i+1, pid[i]);
            }
            printf("\nProcess ID Array initialized successfully.");
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nEnter arrival time for each process.");
            //Array to store the arrival times of all processes
            for(int i = 0; i < n; i++){
                printf("\nArrival time for Process ID %d: ", pid[i]);
                scanf("%d", &at[i]);
            }
            printf("\n-----------------------------------------------------------------------------------");
            printf("\nEnter burst time (execution time) for each process.");
            //Array to store the burst times of all processes
            for(int i = 0; i < n; i++){
                printf("\nBurst time for Process ID %d: ", pid[i]);
                scanf("%d", &bt[i]);
            }
            printf("\n-----------------------------------------------------------------------------------");
            //Array to store the waiting times of all processes
            //n is the process id.
            //If wt[1] = 5, then it implies that the process with process id 1 has a waiting time of 5 ms.
            wt[0] = 0;
            //The process with process id 0 has a wait time of 0 ms, in a system where all processes arrive at 0 ms.
            //Array to store the turnaround time of all processes
            int quantum;
            switch(ch_algo)
            {
                case 1:
                    printf("\nYou selected SRTN!");
                    srtn(pid, at, bt, wt, tat, n);
                    break;
                case 2:
                    printf("\nYou selected RR!");
                    printf("\nEnter time quantum: ");
                    scanf("%d", &quantum);
                    rr(pid, at, bt, n, quantum);
                    break;
                case 3:
                    printf("\nYou selected Priority!");
                    printf("\n-----------------------------------------------------------------------------------");
                    printf("\nEnter burst time (execution time) for each process.");
                    //Array to store the burst times of all processes
                    for(int i = 0; i < n; i++){
                        printf("\nBurst time for Process ID %d: ", pid[i]);
                        scanf("%d", &p[i]);
                    }
                    for(int i = 0; i < n; i++)
                        printf("\nProcess %d has got Priority %d.", i+1, p[i]);
                    priority(pid, at, bt, wt, tat, p, n);
                    break;
                default:
                    printf("\nInvalid choice!");
            }
        }
        printf("\nDo you want to run the program again? Enter '1' else any integer.\nEnter your choice: ");
        scanf("%d", &ch_run);
        if(ch_run == 1){
            continue;
        } else {
            break;
        }
    }
    return 0;
}