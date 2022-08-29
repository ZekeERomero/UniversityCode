/*********************************************
 * Id: rome9162
 *
 * This program computes the restriced tower of hanoi problem
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

//2
//7
//21
//59

char *array;

void cyclicShort(int);
void cyclicLong(int);
void printChar(int);

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      printf("Need a single integer input\n");
   }
   else
   {
      array = malloc(sizeof(int)*atoi(argv[1]));
      int i;
      for(i = 1; i <= atoi(argv[1]); i++)
      {
         array[i] = 'A';
      }

      cyclicLong(atoi(argv[1]));
   }
   return 0;
}

void cyclicShort(int n)
{
   if (n > 0)
   {
      cyclicLong(n-1);
      printChar(n);
      cyclicLong(n-1);
   }
   return;
}

void cyclicLong(int n)
{
   if (n > 0)
   {
      cyclicLong(n-1);
      printChar(n);
      cyclicShort(n-1);
      printChar(n);
      cyclicLong(n-1);
   }
   return;
}

void printChar(n)
{
   if(array[n] == 'A')
   {
      printf("A to B\n");
      array[n] = 'B';
   }
   else if(array[n] == 'B')
   {
      printf("B to C\n");
      array[n] = 'C';
   }
   else if(array[n] == 'C')
   {
      printf("C to A\n");
      array[n] = 'A';
   }
   return;
}
