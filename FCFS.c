#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_PROCESS 200

void scan_from_file(FILE *in, int process_id[], int burst_time[], int arrival_time[]);
void print_to_file(FILE *out, int process_id[], int burst_time[], int arrival_time[]);

int main()
{
   int process_id[NUMBER_OF_PROCESS] = {0}, burst_time[NUMBER_OF_PROCESS] = {0}, arrival_time[NUMBER_OF_PROCESS] = {0};
   // int turnaround_time[200], wait_time[200];

   FILE *in;
   if ((in = fopen("processes", "r")) == NULL)
   {
      printf("Error - Opening processes file.");
      exit(1);
   }

   FILE *out;
   if ((out = fopen("FCFS.out", "w")) == NULL)
   {
      printf("Error - Opening out file.");
      exit(1);
   }

   scan_from_file(in, process_id, burst_time, arrival_time);
   print_to_file(out, process_id, burst_time, arrival_time);

   fclose(in);
   fclose(out);
   return 0;
}

void scan_from_file(FILE *in, int process_id[], int burst_time[], int arrival_time[])
{
   int a, b, c;

   int i = 0;
   while (fscanf(in, "%d %d %d", &a, &b, &c) != -1)
   {
      process_id[i] = a;
      burst_time[i] = b;
      arrival_time[i] = c;
      i++;
   }
}

void print_to_file(FILE *out, int process_id[], int burst_time[], int arrival_time[])
{
   fprintf(out, "%s %s %s %s %s\n", "PID", "B", "A", "W", "T");
   int i;
   for (i = 0; i < NUMBER_OF_PROCESS; i++)
   {
      fprintf(out, "%d %d %d\n", process_id[i], burst_time[i], arrival_time[i]);
   }
}
