#include "circularbuffer.h"
#include <string.h>

void cb_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
    memset(cb->buffer, 0, CB_MAX_SIZE);
}

int cb_write(CircularBuffer *cb, const char *data, int len) {
    if (cb->size + len > CB_MAX_SIZE) return -1;
    for (int i = 0; i < len; i++) {
        cb->buffer[cb->head] = data[i];
        cb->head = (cb->head + 1) % CB_MAX_SIZE;
        cb->size++;
    }
    return len;
}

int cb_read(CircularBuffer *cb, char *data, int len) {
    if (cb->size < len) len = cb->size;
    for (int i = 0; i < len; i++) {
        data[i] = cb->buffer[cb->tail];
        cb->tail = (cb->tail + 1) % CB_MAX_SIZE;
        cb->size--;
    }
    return len;
}

int cb_is_empty(CircularBuffer *cb) {
    return cb->size == 0;
}

int cb_is_full(CircularBuffer *cb) {
    return cb->size == CB_MAX_SIZE;
}
