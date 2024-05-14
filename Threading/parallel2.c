#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define THREAD_NO 10
#define SUB_ARRAY_SIZE (ARRAY_SIZE / THREAD_NO)

int sums[THREAD_NO]; // Array to hold results from each thread
pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for updating total_sum

typedef struct {
    int index;
    int* subArray;
} ThreadArgs;

void* thread_sum(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    int index = args->index;

    for (int i = 0; i < SUB_ARRAY_SIZE; i++) {
        sums[index] += args->subArray[i]; // Sum the sub-array
    }

    free(arg); // Free the allocated ThreadArgs struct
    return NULL;
}

int main() {
    pthread_t threads[THREAD_NO];
    int num[THREAD_NO][SUB_ARRAY_SIZE];
    int total_sum = 0;

    // Seed the random number generator
    srand(100);

    // Initialize arrays with random numbers
    for (int i = 0; i < THREAD_NO; i++) {
        for (int j = 0; j < SUB_ARRAY_SIZE; j++) {
            num[i][j] = rand() % 100;
        }
    }

    // Create threads, each with its own sub-array to process
    for (int i = 0; i < THREAD_NO; i++) {
        ThreadArgs* args = malloc(sizeof(ThreadArgs));
        if (args == NULL) {
            fprintf(stderr, "Failed to allocate memory for thread arguments\n");
            exit(EXIT_FAILURE);
        }
        args->index = i;
        args->subArray = num[i];

        if (pthread_create(&threads[i], NULL, thread_sum, args) != 0) {
            perror("Failed to create thread");
            free(args);
        }
    }

    // Join threads and compute the total sum
    for (int i = 0; i < THREAD_NO; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
        
        pthread_mutex_lock(&sum_mutex); // Lock the mutex before updating total_sum
        total_sum += sums[i]; // Aggregate the sums from each thread
        pthread_mutex_unlock(&sum_mutex); // Unlock the mutex after updating
    }

    // Output the total sum
    printf("Total Sum with Synchronization = %d\n", total_sum);

    // Destroy the mutex after use
    pthread_mutex_destroy(&sum_mutex);

    return 0;
}

