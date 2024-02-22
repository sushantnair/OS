#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

void fcfs(int pid[], int at[], int bt[], int wt[], int tat[], int size)
{
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nInside FCFS function...");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nPrinting initial table...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nForming table...");
    // Calculate waiting times for FCFS
    wt[0] = 0;  // The first process has no waiting time
    for (int i = 1; i < size; i++) {
        // Calculate waiting time for the current process
        wt[i] = wt[i - 1] + bt[i - 1];
        // If the current process arrived after the completion of the previous process,
        // adjust the waiting time accordingly
        if (at[i] > wt[i]) {
            wt[i] += at[i] - wt[i];
        }
    }
    // Calculate turnaround times for FCFS
    for (int i = 0; i < size; i++) {
        tat[i] = wt[i] + bt[i];
    }
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nPrinting final table...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------------------");
    //IMPLEMENTATION SUCCESSFUL
}

void sjf(int pid[], int at[], int bt[], int wt[], int tat[], int size) {
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nInside SJF function...");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nPrinting data...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n-----------------------------------------------------------------------------------\n");
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
    printf("\n-----------------------------------------------------------------------------------\n");
    //IMPLEMENTED SUCCESSFULLY
}

void priority(int pid[], int at[], int bt[], int wt[], int tat[], int p[], int size)
{
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nInside Priority function...");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\nPrinting data...");
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(int i = 0; i < size; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    int completion_time[size], remaining_time[size];
    int total_wt = 0, total_tat = 0;
    // Initialize remaining_time array with burst times
    for (int i = 0; i < size; i++) {
        remaining_time[i] = bt[i];
    }
    int current_time = 0;
    int completed = 0;
    printf("\n-----------------------------------------------------------------------------------\n");
    printf("Process\tPriority\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    while (completed < size) {
        int highest_priority = -1;
        for (int i = 0; i < size; i++) {
            if (at[i] <= current_time && remaining_time[i] > 0) {
                if (highest_priority == -1 || p[i] < p[highest_priority]) {
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
            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", pid[process], p[process], at[process], bt[process], completion_time[process], tat[process], wt[process]);
        }
    }
    float avg_wt = (float)total_wt / size;
    float avg_tat = (float)total_tat / size;
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n-----------------------------------------------------------------------------------");
    //SUCCESSFUL IMPLEMENTATION
}

int main() 
{
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n--------------------Non-Preemptive Scheduling Algorithm Program--------------------");
    printf("\n-----------------------------------------------------------------------------------");
    int ch_run;
    while(0 < 1){
        fflush(stdin);
        printf("\nEnter 1 for First Come First Serve\nEnter 2 for Shortest Job First\nEnter 3 for Priority\nEnter choice: ");
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
            switch(ch_algo)
            {
                case 1:
                    printf("\nYou selected FCFS!");
                    fcfs(pid, at, bt, wt, tat, n);
                    break;
                case 2:
                    printf("\nYou selected SJF!");
                    sjf(pid, at, bt, wt, tat, n);
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
            switch(ch_algo)
            {
                case 1:
                    printf("\nYou selected FCFS!");
                    fcfs(pid, at, bt, wt, tat, n);
                    break;
                case 2:
                    printf("\nYou selected SJF!");
                    sjf(pid, at, bt, wt, tat, n);
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