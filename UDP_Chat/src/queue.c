#include "queue.h"
#include <stdlib.h>
#include <string.h>

void queue_init(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    for (int i = 0; i < QUEUE_MAX_SIZE; i++) {
        q->items[i] = NULL;
    }
}

int queue_enqueue(Queue *q, const char *item) {
    if (queue_is_full(q)) return -1;
    q->rear = (q->rear + 1) % QUEUE_MAX_SIZE;
    q->items[q->rear] = strdup(item); // Copy string
    q->size++;
    return 0;
}

char *queue_dequeue(Queue *q) {
    if (queue_is_empty(q)) return NULL;
    char *item = q->items[q->front];
    q->items[q->front] = NULL;
    q->front = (q->front + 1) % QUEUE_MAX_SIZE;
    q->size--;
    return item; // Caller must free the returned string
}

int queue_is_empty(Queue *q) {
    return q->size == 0;
}

int queue_is_full(Queue *q) {
    return q->size == QUEUE_MAX_SIZE;
}
