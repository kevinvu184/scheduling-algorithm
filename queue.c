#include <stdio.h>

#include <stdlib.h>

typedef struct P {
    int id;
    int bt;
    int at;
} P;

typedef struct node {
    P p;
    struct node *next;
} node;

void enqueue(node **head, P p) {
    node *new = malloc(sizeof(node));
    if (!new) return;
    new->p = p;
    new->next = *head;
    *head = new;
}

void dequeue(node **head) {
    node *current, *prev = NULL;
    if (*head == NULL) return;
    current = *head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    P p = current->p;
    free(current);
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
}

int main() {
    node *head = NULL;
    P p;

    P p1 = {1,2,3};
    P p2 = {4,5,6};
    P p3 = {7,8,9};
    P p4 = {10,11,12};
    enqueue(&head, p1);
    enqueue(&head, p2);
    enqueue(&head, p3);
    enqueue(&head, p4);

    print_list(head);

    dequeue(&head);
    dequeue(&head);
    enqueue(&head, p3);
    enqueue(&head, p4);

    print_list(head);
    return 0;
}