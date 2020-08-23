#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_PROCESS 200

void scan_from_file(FILE *in, int process_id[], int burst_time[], int arrival_time[]);

void calc_complete_time(int complete_time[], int burst_time[]);
void calc_turnaround_time(int turnaround_time[], int arrival_time[], int complete_time[]);
void calc_waiting_time(int wait_time[], int burst_time[], int turnaround_time[]);

void print_to_file(FILE *out, int process_id[], int burst_time[], int arrival_time[], int complete_time[], int turnaround_time[], int wait_time[]);

int main()
{
   int process_id[NUMBER_OF_PROCESS] = {0}, burst_time[NUMBER_OF_PROCESS] = {0}, arrival_time[NUMBER_OF_PROCESS] = {0};
   int complete_time[NUMBER_OF_PROCESS] = {0}, turnaround_time[NUMBER_OF_PROCESS] = {0}, waiting_time[NUMBER_OF_PROCESS] = {0};

   // Open input - output file
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

   calc_complete_time(complete_time, burst_time);
   calc_turnaround_time(turnaround_time, arrival_time, complete_time);
   calc_waiting_time(waiting_time, burst_time, turnaround_time);

   print_to_file(out, process_id, burst_time, arrival_time, complete_time, turnaround_time, waiting_time);

   // Close input - output file
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

void calc_complete_time(int complete_time[], int burst_time[])
{
   int temp = 0;

   int i;
   for (i = 0; i < NUMBER_OF_PROCESS; i++)
   {
      temp += burst_time[i];
      complete_time[i] += temp;
   }
}

void calc_turnaround_time(int turnaround_time[], int arrival_time[], int complete_time[])
{
   int i;
   for (i = 0; i < NUMBER_OF_PROCESS; i++)
   {
      turnaround_time[i] = complete_time[i] - arrival_time[i];
   }
}

void calc_waiting_time(int wait_time[], int burst_time[], int turnaround_time[])
{
   int i;
   for (i = 0; i < NUMBER_OF_PROCESS; i++)
   {
      wait_time[i] = turnaround_time[i] - burst_time[i];
   }
}

void print_to_file(FILE *out, int process_id[], int burst_time[], int arrival_time[], int complete_time[], int turnaround_time[], int wait_time[])
{
   fprintf(out, "%s %s %s %s %s %s\n", "PID", "B", "A", "C", "T", "W");

   int i;
   for (i = 0; i < NUMBER_OF_PROCESS; i++)
   {
      fprintf(out, "%d %d %d %d %d %d\n", process_id[i], burst_time[i], arrival_time[i], complete_time[i], turnaround_time[i], wait_time[i]);
   }
}
