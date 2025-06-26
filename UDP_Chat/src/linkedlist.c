#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

void linkedlist_init(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

int linkedlist_add(LinkedList *list, const char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return -1;
    new_node->data = strdup(data);
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    return 0;
}

char *linkedlist_remove(LinkedList *list) {
    if (!list->head) return NULL;
    Node *temp = list->head;
    char *data = temp->data;
    list->head = temp->next;
    free(temp);
    list->size--;
    return data; // Caller must free the returned string
}

void linkedlist_free(LinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}
