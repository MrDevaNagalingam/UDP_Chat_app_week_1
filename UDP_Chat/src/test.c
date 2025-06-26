#include <stdio.h>
#include "queue.h"
#include "linkedlist.h"
#include "circularbuffer.h"

int main() {
    // Test Queue
    Queue q;
    queue_init(&q);
    queue_enqueue(&q, "Message 1");
    queue_enqueue(&q, "Message 2");
    char *msg = queue_dequeue(&q);
    printf("Queue: Dequeued '%s'\n", msg);
    free(msg);

    // Test Linked List
    LinkedList list;
    linkedlist_init(&list);
    linkedlist_add(&list, "Node 1");
    linkedlist_add(&list, "Node 2");
    msg = linkedlist_remove(&list);
    printf("Linked List: Removed '%s'\n", msg);
    free(msg);
    linkedlist_free(&list);

    // Test Circular Buffer
    CircularBuffer cb;
    cb_init(&cb);
    cb_write(&cb, "Hello", 5);
    char buffer[10] = {0};
    cb_read(&cb, buffer, 5);
    printf("Circular Buffer: Read '%s'\n", buffer);

    return 0;
}
