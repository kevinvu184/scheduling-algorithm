#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#define NUMBER_OF_PROCESS 200
#define TIME_QUANTUM 2
#define SWITCH_TIME 0.1

typedef struct P
{
    int id;
    int bt;
    int at;
    int sl;
    int fl;
    int ct;
    int tt;
    int wt;
} P;

typedef struct node
{
    P p;
    struct node *next;
} node;

void scan_from_file(FILE *in, P p[]);

void print_to_file(FILE *out, P p[]);

int isDone(P p[]);

int range(int cct, P p[]);

void enqueue(node **head, P p);

P dequeue(node **head);

int main()
{
    P p[NUMBER_OF_PROCESS];

    FILE *in;
    if ((in = fopen("processes", "r")) == NULL)
    {
        printf("Error - Opening processes file.");
        exit(1);
    }

    FILE *out;
    if ((out = fopen("RR.txt", "w")) == NULL)
    {
        printf("Error - Opening RR.txt file.");
        exit(1);
    }

    scan_from_file(in, p);

    int cct = 0;
    int i = 0;
    int done = 0;
    while (!done)
    {
        cct += p[i].bt;
        p[i].ct += cct;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].fl = 1;

        done = isDone(p);
        if (done)
        {
            break;
        }
        i++;
    }

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
        p[i].id = a;
        p[i].bt = b;
        p[i].at = c;
        p[i].sl = (int)ceil((float)p[i].bt / TIME_QUANTUM);
        p[i].fl = 0;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;

        i++;
    }
}

void print_to_file(FILE *out, P p[])
{
    fprintf(out, "%5s%5s%5s%5s%5s%5s%5s%5s\n", "I", "B", "A", "S", "C", "T", "W", "D");

    int i;
    for (i = 0; i < NUMBER_OF_PROCESS; i++)
    {
        fprintf(out, "%5d%5d%5d%5d%5d%5d%5d%5d\n", p[i].id, p[i].bt, p[i].at, p[i].sl, p[i].ct, p[i].tt, p[i].wt, p[i].fl);
    }
}

int isDone(P p[])
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

int range(int cct, P p[])
{
    int j = 0;
    while (cct > p[j].at)
    {
        j++;
    }
    return j - 1;
}

void enqueue(node **head, P p)
{
    node *new = malloc(sizeof(node));
    if (!new)
        return;
    new->p = p;
    new->next = *head;
    *head = new;
}

P dequeue(node **head)
{
    node *current, *prev = NULL;
    P p = {-1, -1, -1, -1, -1, -1, -1, -1};
    if (*head == NULL)
        return p;
    current = *head;
    while (current->next != NULL)
    {
        prev = current;
        current = current->next;
    }
    p = current->p;
    free(current);
    if (prev)
        prev->next = NULL;
    else
        *head = NULL;
    return p;
}