#include <stdio.h>
#include <stdlib.h>

// Change this equal to the number of process in the input file.
#define NUMBER_OF_PROCESS 200
// Change this to the input file name
#define IN_FILE "processes"
// A process struct
typedef struct P
{
    // Burst Time
    int bt;
    // Arrival Time
    int at;
    // Flag indicate is done or not
    int fl;
    // Completion time
    float ct;
    // Turn around time
    float tt;
    // Waiting time
    float wt;
} P;
// Queue node
typedef struct node
{
    int i;
    struct node *next;
} node;
// Method prototype
void fcfs(P p[]);
void scan_from_file(FILE *in, P p[]);
void print_to_file(FILE *out, P p[]);
int is_done(P p[]);
int available_processes(int cct, P p[]);
void enqueue(node **head, int i);
int dequeue(node **head);

int main()
{
    P p[NUMBER_OF_PROCESS];

    FILE *in;
    if ((in = fopen(IN_FILE, "r+")) == NULL)
    {
        printf("Error - Opening processes file.");
        exit(1);
    }
    FILE *out;
    if ((out = fopen("FCFS.txt", "w+")) == NULL)
    {
        printf("Error - Opening FCFS.txt file.");
        exit(1);
    }
    scan_from_file(in, p);

    // Main First Come First Serve Logic
    fcfs(p);

    print_to_file(out, p);
    fclose(in);
    fclose(out);

    return 0;
}

void fcfs(P p[])
{
    // Current Completion Time, Iterator
    float cct = 0;
    int i = 0;

    // The queue containing the processes
    node *ready = NULL;
    enqueue(&ready, i);

    // Loop until all done-flag is 1 (done)
    while (!is_done(p))
    {
        i = dequeue(&ready);

        // If there is an exist process in the current completion time frame that is not processed
        // Process it.
        // Otherwise, add 1 second to the current completion time.
        if (i != -1)
        {
            cct += p[i].bt;
            p[i].ct += cct;
            p[i].tt = p[i].ct - p[i].at;
            p[i].wt = p[i].tt - p[i].bt;
            p[i].fl = 1;
        }
        else
        {
            cct += 1;
        }

        // Check whether there is a new available process with the current completion time frame
        // To add to the queue
        int available_i = available_processes(cct, p);
        int j = 0;
        while (j < available_i)
        {
            if (p[j].fl == 0)
            {
                enqueue(&ready, j);
            }
            j++;
        }
    }
}

// Helper methods
void scan_from_file(FILE *in, P p[])
{
    int a, b, c;
    int i = 0;
    while (fscanf(in, "%d %d %d", &a, &b, &c) != -1)
    {
        p[i].bt = b;
        p[i].at = c;
        p[i].fl = 0;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;
        i++;
    }
}

void print_to_file(FILE *out, P p[])
{
    fprintf(out, "%7s%7s%7s%7s%7s%7s\n", "I", "B", "A", "C", "T", "W");
    int i = 0;
    while (i < NUMBER_OF_PROCESS)
    {
        fprintf(out, "%7d%7d%7d%7.1f%7.1f%7.1f\n", i, p[i].bt, p[i].at, p[i].ct, p[i].tt, p[i].wt);
        i++;
    }
}

int is_done(P p[])
{
    int i = 0;
    int is_done = 1;
    while (i < NUMBER_OF_PROCESS)
    {
        if (p[i].fl == 0)
        {
            is_done = 0;
            break;
        }
        i++;
    }
    return is_done;
}

int available_processes(int cct, P p[])
{
    int i = 0;
    while (i < NUMBER_OF_PROCESS)
    {
        if (cct < p[i].at)
        {
            break;
        }
        i++;
    }
    return i;
}

void enqueue(node **head, int i)
{
    node *new = malloc(sizeof(node));

    if (!new)
    {
        return;
    }

    if (*head != NULL)
    {
        node *curr = *head;

        if (curr->i == i)
        {
            return;
        }
        else
        {
            while (curr->next != NULL)
            {
                curr = curr->next;
                if (curr->i == i)
                    return;
            }
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
    {
        return -1;
    }

    curr = *head;

    while (curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }

    i = curr->i;

    free(curr);

    if (prev)
    {
        prev->next = NULL;
    }
    else
    {
        *head = NULL;
    }

    return i;
}
