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
    float ct;
    // Turn around time
    float tt;
    // Waiting time
    float wt;
} P;

void scan_from_file(FILE *in, P p[]);

void print_to_file(FILE *out, P p[]);

int is_done(P p[]);

int available_processes(int cct, P p[]);

void sjf(P p[]);

int main()
{
    P p[NUMBER_OF_PROCESS];

    FILE *in;
    if ((in = fopen("processes", "r+")) == NULL)
    // if ((in = fopen("./unit_test/SJF02.test", "r")) == NULL)
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

    sjf(p);

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
    while (cct >= p[i].at && i < NUMBER_OF_PROCESS)
    {
        i++;
    }
    return i;
}

void sjf(P p[])
{
    // Current Completion Time, Iterator, Done Flag
    float cct = 0;
    int i = 0;
    while (!is_done(p))
    {
        cct += p[i].bt;
        p[i].ct += cct;
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        p[i].fl = 1;

        // Last index, largest initial min, iterator
        int last = available_processes(cct, p), min = 9999, j = 0;
        while (j < last)
        {
            if (p[j].bt < min && p[j].fl == 0)
            {
                min = p[j].bt;
                i = j;
            }
            j++;
        }
    }
}