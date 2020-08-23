#include <stdio.h>
#include <stdlib.h>

int main()
{
   int a, b, c;
   FILE *file;

   if ((file = fopen("processes", "r")) == NULL)
   {
      printf("Error! opening file");
      exit(1);
   }

   while (fscanf(file, "%d %d %d", &a, &b, &c) != -1)
   {
      printf("%d %d %d\n", a, b, c);
   }
   return 0;
}
