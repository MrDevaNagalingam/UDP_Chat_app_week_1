#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_MAX_SIZE 100

typedef struct {
    char *items[QUEUE_MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// Function prototypes
void queue_init(Queue *q);
int queue_enqueue(Queue *q, const char *item);
char *queue_dequeue(Queue *q);
int queue_is_empty(Queue *q);
int queue_is_full(Queue *q);

#endif // QUEUE_H

