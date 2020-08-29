#include <stdio.h>

#include <stdlib.h>

// Change this equal to the no of process in the input file.
#define NUMBER_OF_PROCESS 200

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
    int ct;
    // Turn around time
    int tt;
    // Waiting time
    int wt;
} P;

void scan_from_file(FILE *in, P p[]);

void print_to_file(FILE *out, P p[]);

int is_done(P p[]);

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
    if ((out = fopen("FCFS.txt", "w")) == NULL)
    {
        printf("Error - Opening FCFS.txt file.");
        exit(1);
    }

    scan_from_file(in, p);

    // Current Completion Time, Iterator, Done Flag
    int cct = 0, i = 0;
    // Infinite loop that is only end if all the process are processed
    for (;;)
    {
        cct += (p[i].at > cct) ? p[i].bt + (p[i].at - cct) : p[i].bt;
        p[i].ct += cct;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].fl = 1;

        if (is_done(p))
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