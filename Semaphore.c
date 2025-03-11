#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 5
sem_t semaphore;
void* accessResource(void* arg) {
    int threadId = *(int*)arg;
    free(arg);
    printf("Thread %d is waiting to access the resource.\n", threadId);
    if (sem_wait(&semaphore) != 0) {
        perror("Semaphore wait failed");
        pthread_exit(NULL);
    }
    printf("Thread %d is accessing the resource.\n", threadId);
    sleep(2);
    printf("Thread %d has finished accessing the resource.\n", threadId);
    if (sem_post(&semaphore) != 0) {
        perror("Semaphore post failed");
        pthread_exit(NULL);
    }
    return NULL;
}
int main() {
    sem_init(&semaphore, 0, 3);
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        int* threadId = malloc(sizeof(int));
        if (threadId == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *threadId = i;
        if (pthread_create(&threads[i], NULL, accessResource, threadId) != 0) {
            perror("Failed to create thread");
            free(threadId);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;
}