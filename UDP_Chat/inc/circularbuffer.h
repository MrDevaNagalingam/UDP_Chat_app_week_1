#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#define CB_MAX_SIZE 1024

typedef struct {
    char buffer[CB_MAX_SIZE];
    int head;
    int tail;
    int size;
} CircularBuffer;

// Function prototypes
void cb_init(CircularBuffer *cb);
int cb_write(CircularBuffer *cb, const char *data, int len);
int cb_read(CircularBuffer *cb, char *data, int len);
int cb_is_empty(CircularBuffer *cb);
int cb_is_full(CircularBuffer *cb);

#endif // CIRCULARBUFFER_H
