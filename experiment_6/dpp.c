#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 5
#define LEFT (philo + N - 1) % N
#define RIGHT (philo + 1) % N
pthread_t philosophers[N];
pthread_mutex_t forks[N];
int eat_count[N];
int max_eat_count = 1;  // Maximum number of times a philosopher can eat
void grab_forks(int philo) {
    pthread_mutex_lock(&forks[philo]);
    pthread_mutex_lock(&forks[LEFT]);
    printf("Philosopher %d has taken up fork %d and fork %d\n", philo + 1, LEFT + 1, philo + 1);
}
void put_away_forks(int philo) {
    pthread_mutex_unlock(&forks[philo]);
    pthread_mutex_unlock(&forks[LEFT]);
    printf("Philosopher %d has put down fork %d and fork %d\n", philo + 1, LEFT + 1, philo + 1);
}
void* philosopher(void* num) {
    int philo = *((int*)num);
    while (eat_count[philo] < max_eat_count) {
        printf("Philosopher %d is thinking\n", philo + 1);
        sleep(1);
        grab_forks(philo);
        printf("Philosopher %d is eating\n", philo + 1);
        eat_count[philo]++;
        sleep(1);
        put_away_forks(philo);
        printf("Philosopher %d has eaten once\n", philo + 1);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main() {
    int i;
    int philo_numbers[N];  
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        eat_count[i] = 0;
        philo_numbers[i] = i;
    }
    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philo_numbers[i]);
    }
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}
//WARNING: Do not press the "run" button as it doesn't have proper path configuration
//in order to run C programs handling threads and semaphores.
//Instead, open the terminal
//Ensure that you are in the correct folder. For this code, it is:
//PS C:\Users\hp\OneDrive - somaiya.edu\Desktop\SEM V\OS\EXPT-6>
//Next, enter this command:  gcc -g -pthread dpp.c -o philosopher
//Next, enter this command: .\philosopher.exe
//The code should run