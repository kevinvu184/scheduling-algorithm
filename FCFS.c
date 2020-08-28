#include <stdio.h>

#include <stdlib.h>

#define NUMBER_OF_PROCESS 200

typedef struct P
{
    int id;
    int bt;
    int at;
    int fl;
    int ct;
    int tt;
    int wt;
} P;

void scan_from_file(FILE *in, P p[]);

void print_to_file(FILE *out, P p[]);

int isDone(P p[]);

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
    if ((out = fopen("FCFS.txt", "w")) == NULL)
    {
        printf("Error - Opening FCFS.txt file.");
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
        p[i].fl = 0;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;

        i++;
    }
}

void print_to_file(FILE *out, P p[])
{
    fprintf(out, "%5s%5s%5s%5s%5s%5s%5s\n", "I", "B", "A", "C", "T", "W", "D");

    int i;
    for (i = 0; i < NUMBER_OF_PROCESS; i++)
    {
        fprintf(out, "%5d%5d%5d%5d%5d%5d%5d\n", p[i].id, p[i].bt, p[i].at, p[i].ct, p[i].tt, p[i].wt, p[i].fl);
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