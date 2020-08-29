#include <stdio.h>

#include <stdlib.h>

// Change this equal to the no of process in the input file.
#define NUMBER_OF_PROCESS 200
#define QUANTUM 2
#define SWITCH 0.1

// A process struct
typedef struct P
{
    // Burst Time
    int bt;
    // Arrival Time
    int at;
    // Remaining Burst Time
    int re;
    // Flag indicate is done or not
    int fl;
    // Completion time
    int ct;
    // Turn around time
    int tt;
    // Waiting time
    int wt;
} P;

typedef struct node
{
    int i;
    struct node *next;
} node;

void scan_from_file(FILE *in, P p[]);

void print_to_file(FILE *out, P p[]);

int is_done(P p[]);

int available_processes(int cct, P p[]);

void enqueue(node **head, int i);

int dequeue(node **head);

void print_list(node *head);

int main()
{
    P p[NUMBER_OF_PROCESS];

    FILE *in;
    if ((in = fopen("processes", "r")) == NULL)
    // if ((in = fopen("./unit_test/FCFS02.test", "r")) == NULL)
    {
        printf("Error - Opening processes file.");
        exit(1);
    }

    FILE *out;
    if ((out = fopen("RR.txt", "w+")) == NULL)
    {
        printf("Error - Opening RR.txt file.");
        exit(1);
    }

    scan_from_file(in, p);

    print_to_file(out, p);

    fclose(in);

    fclose(out);

    return 0;
}

void scan_from_file(FILE *in, P p[])
{
    int a, b, c;
    int i = 0;
    while (fscanf(in, "%d %d %d", &a, &b, &c) != -1)
    {
        p[i].bt = b;
        p[i].at = c;
        p[i].re = p[i].bt;
        p[i].fl = 0;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;
        i++;
    }
}

void print_to_file(FILE *out, P p[])
{
    fprintf(out, "%5s%5s%5s%5s%5s%5s\n", "I", "B", "A", "C", "T", "W");
    int i = 0;
    while (i < NUMBER_OF_PROCESS)
    {
        fprintf(out, "%5d%5d%5d%5d%5d%5d\n", i, p[i].bt, p[i].at, p[i].ct, p[i].tt, p[i].wt);
        i++;
    }
}

int is_done(P p[])
{
    int i = 0;
    while (i < NUMBER_OF_PROCESS)
    {
        if (p[i].fl == 0)
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int available_processes(int cct, P p[])
{
    int i = 0;
    while (cct >= p[i].at)
    {
        i++;
    }
    return i;
}

void enqueue(node **head, int i)
{
    node *new = malloc(sizeof(node));
    if (!new)
        return;

    if (*head != NULL)
    {
        node *curr = *head;
        if (curr->i == i)
            return;
        else
            while (curr->next != NULL)
            {
                curr = curr->next;
                if (curr->i == i)
                    return;
            }
    }

    new->i = i;
    new->next = *head;
    *head = new;
}

int dequeue(node **head)
{
    node *curr, *prev = NULL;
    int i = -1;
    if (*head == NULL)
        return -1;
    curr = *head;
    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }
    i = curr->i;
    free(curr);
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
    return i;
}

void print_list(node *head)
{
    node *curr = head;
    while (curr != NULL)
    {
        printf("%d ", curr->i);
        curr = curr->next;
    }
    printf("\n");
}