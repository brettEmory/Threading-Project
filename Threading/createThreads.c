#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NO 10

void *mythread(void *arg) {
    int id = *(int *)arg; // Dereference the pointer to get the thread's unique ID
    printf("my id is %d\n", id); // Print the ID
    free(arg); // Free the allocated memory for the ID
    return NULL; // Exit the thread
}

int main() {
    pthread_t p[THREAD_NO]; // Array to hold thread IDs
	int i = 0;
    for(int i = 0; i < THREAD_NO; i++) {
        int *id = malloc(sizeof(*id)); // Allocate memory for the thread ID
        if (id == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(EXIT_FAILURE); // Exit if memory allocation failed
        }
        *id = i; // Set the thread ID to the loop counter
        if(pthread_create(&p[i], NULL, mythread, id) != 0) {
            perror("pthread_create failed"); // Check for errors in thread creation
            free(id); // Free the allocated memory if thread creation fails
        }
    }

    // Wait for all threads to finish
    for(int i = 0; i < THREAD_NO; i++) {
        if(pthread_join(p[i], NULL) != 0) {
            perror("pthread_join failed"); // Check for errors in joining the thread
        }
    }

    return 0; // Exit the program
}
