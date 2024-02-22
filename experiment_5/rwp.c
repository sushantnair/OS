#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
int sharedResource = 0;
int readerCount = 0;
sem_t mutex, writeSemaphore;
int maxOperations = 20; // Number of read and write operations
int currentOperation = 0;
void *reader(void *arg) {
    while (currentOperation < maxOperations) {
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&writeSemaphore);
        }
        sem_post(&mutex);
        // Read the shared resource
        printf("Reader %ld reads: %d\n", (long)arg, sharedResource);
        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&writeSemaphore);
        }
        sem_post(&mutex);
        currentOperation++;
        // Simulate some reading time
        sleep(1);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    while (currentOperation < maxOperations) {
        sem_wait(&writeSemaphore);
        // Modify the shared resource
        sharedResource++;
        printf("Writer %ld writes: %d\n", (long)arg, sharedResource);
        sem_post(&writeSemaphore);
        currentOperation++;
        // Simulate some writing time
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t readerThreads[3];
    pthread_t writerThreads[2];
    sem_init(&mutex, 0, 1);
    sem_init(&writeSemaphore, 0, 1);
    for (long i = 0; i < 3; i++) {
        pthread_create(&readerThreads[i], NULL, reader, (void *)i);
    }
    for (long i = 0; i < 2; i++) {
        pthread_create(&writerThreads[i], NULL, writer, (void *)i);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(readerThreads[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writerThreads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&writeSemaphore);
    return 0;
}
