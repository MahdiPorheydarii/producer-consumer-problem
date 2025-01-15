#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <buffer.h>

buffer_item buffer[BUFFER_SIZE];
int in = 0, out = 0;
HANDLE empty, full, mutex;

void initialize_synchronization() {
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    if (empty == NULL || full == NULL || mutex == NULL) {
        fprintf(stderr, "Error initializing synchronization primitives\n");
        exit(-1);
    }
}

int insert_item(buffer_item item) {
    WaitForSingleObject(empty, INFINITE);
    WaitForSingleObject(mutex, INFINITE);

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    ReleaseMutex(mutex);
    ReleaseSemaphore(full, 1, NULL);

    return 0;
}

int remove_item(buffer_item *item) {
    WaitForSingleObject(full, INFINITE);
    WaitForSingleObject(mutex, INFINITE);

    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    ReleaseMutex(mutex);
    ReleaseSemaphore(empty, 1, NULL);

    return 0;
}

DWORD WINAPI producer(LPVOID param) {
    buffer_item item;
    while (1) {
        Sleep(rand() % 3000 + 1000);
        item = rand() % 100;         

        if (insert_item(item) == 0) {
            printf("Producer produced %d\n", item);
        } else {
            fprintf(stderr, "Error inserting item\n");
        }
    }
    return 0;
}

DWORD WINAPI consumer(LPVOID param) {
    buffer_item item;
    while (1) {
        Sleep(rand() % 3000 + 1000);

        if (remove_item(&item) == 0) {
            printf("Consumer consumed %d\n", item);
        } else {
            fprintf(stderr, "Error removing item\n");
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sleep time> <num producers> <num consumers>\n", argv[0]);
        return -1;
    }

    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    initialize_synchronization();

    HANDLE *producers = (HANDLE *)malloc(num_producers * sizeof(HANDLE));
    HANDLE *consumers = (HANDLE *)malloc(num_consumers * sizeof(HANDLE));

    for (int i = 0; i < num_producers; i++) {
        producers[i] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    }

    for (int i = 0; i < num_consumers; i++) {
        consumers[i] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    }

    Sleep(sleep_time * 1000);

    printf("Terminating the application...\n");
    free(producers);
    free(consumers);

    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);

    return 0;
}