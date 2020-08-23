#include <stdio.h>
#include <stdlib.h>

int main()
{
   int a, b, c;
   
   FILE *in;
   if ((in = fopen("processes", "r")) == NULL)
   {
      printf("Error! opening file");
      exit(1);
   }

   FILE *out;
   if ((out = fopen("FCFS.out", "w")) == NULL)
   {
      printf("Error! opening file");
      exit(1);
   }

   while (fscanf(in, "%d %d %d", &a, &b, &c) != -1)
   {
      fprintf(out, "%d %d %d\n", a, b, c);
   }

   fclose(in);
   fclose(out);
   return 0;
}
