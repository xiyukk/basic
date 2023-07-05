#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 4

typedef struct {
    int buffer[BUFFER_SIZE];
    int count;
    int read_index;
    int write_index;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} shared_buffer_t;

void *image_processing(void *arg) {
    shared_buffer_t *buffer = (shared_buffer_t *)arg;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == BUFFER_SIZE) {
            pthread_cond_wait(&buffer->not_full, &buffer->mutex);
        }

        buffer->buffer[buffer->write_index] = i;
        printf("Image processed: %d\n", i);
        buffer->write_index = (buffer->write_index + 1) % BUFFER_SIZE;
        buffer->count++;

        pthread_cond_signal(&buffer->not_empty);
        pthread_mutex_unlock(&buffer->mutex);

        // sleep(1);
    }

    return NULL;
}

void *model_input(void *arg) {
    shared_buffer_t *buffer = (shared_buffer_t *)arg;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&buffer->mutex);
        while (buffer->count == 0) {
            pthread_cond_wait(&buffer->not_empty, &buffer->mutex);
        }

        int value = buffer->buffer[buffer->read_index];
        printf("Model input received: %d\n", value);
        buffer->read_index = (buffer->read_index + 1) % BUFFER_SIZE;
        buffer->count--;

        pthread_cond_signal(&buffer->not_full);
        pthread_mutex_unlock(&buffer->mutex);

        // sleep(1);
    }

    return NULL;
}

int main() {
    pthread_t image_processing_thread, model_input_thread;
    shared_buffer_t shared_buffer = {
        .count = 0,
        .read_index = 0,
        .write_index = 0,
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .not_empty = PTHREAD_COND_INITIALIZER,
        .not_full = PTHREAD_COND_INITIALIZER,
    };

    pthread_create(&image_processing_thread, NULL, image_processing, &shared_buffer);
    pthread_create(&model_input_thread, NULL, model_input, &shared_buffer);

    pthread_join(image_processing_thread, NULL);
    pthread_join(model_input_thread, NULL);

    return 0;
}