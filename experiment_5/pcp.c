#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
sem_t empty, full, mutex;
void *producer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = i; // Simulate producing an item
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer %ld produced: %d\n", (long)arg, item);
        sem_post(&mutex);
        sem_post(&full);
        // Simulate some production time
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %ld consumed: %d\n", (long)arg, item);
        sem_post(&mutex);
        sem_post(&empty);
        // Simulate some consumption time
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producerThreads[NUM_PRODUCERS];
    pthread_t consumerThreads[NUM_CONSUMERS];
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    for (long i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producerThreads[i], NULL, producer, (void *)i);
    }
    for (long i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumerThreads[i], NULL, consumer, (void *)i);
    }
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producerThreads[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumerThreads[i], NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}