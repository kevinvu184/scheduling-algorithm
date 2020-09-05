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
void sjf(P p[]);
void scan_from_file(FILE *in, P p[]);
void print_to_file(FILE *out, P p[]);
int is_done(P p[]);
int available_processes(int cct, P p[]);

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
    if ((out = fopen("SJF.txt", "w+")) == NULL)
    {
        printf("Error - Opening SJF.txt file.");
        exit(1);
    }
    scan_from_file(in, p);

    // Main Shortest Job First Logic
    sjf(p);

    print_to_file(out, p);
    fclose(in);
    fclose(out);

    return 0;
}

void sjf(P p[])
{
    // Current Completion Time, Iterator, Done Flag
    float cct = 0;
    int i = 0;
    int is_new_process = 1;

    // Loop until all done-flag is 1 (done)
    while (!is_done(p))
    {
        // If there is an exist process in the current completion time frame that is not processed
        // Process it.
        // Otherwise, add 1 second to the current completion time.
        if (is_new_process)
        {
            cct += p[i].bt;
            p[i].ct += cct;
            p[i].tt = p[i].ct - p[i].at;
            p[i].wt = p[i].tt - p[i].bt;
            p[i].fl = 1;
            is_new_process = 0;
        }
        else
        {
            cct++;
        }

        // Check whether there is a new available process with the current completion time frame
        // To add to the queue
        int available_i = available_processes(cct, p);
        int j = 0;
        int min = 9999;
        while (j < available_i)
        {
            if (i != j && p[j].bt < min && p[j].fl == 0)
            {
                min = p[j].bt;
                i = j;
                is_new_process = 1;
            }
            j++;
        }
    }
}

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
