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

void cyclicHanoi(int, char, char, char);

int global = 0;
int roundn = 0;

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      printf("Need a single integer input\n");
   }
   else
   {
      cyclicHanoi(atoi(argv[1]), 'A', 'C', 'B');
   }
   printf("%d\n",global);
   return 0;
}

void cyclicHanoi(int n, char from, char to, char with)
{
   roundn++;
   int roundTemp = roundn;
   if (n == 0)
   {
      printf("s- Move %c to %c\n", from, with);
      global++;
      return;
   }
   if (n == 1)
   {
      printf("%d 0 - Move %c to %c\n", n, from, with);
      printf("%d 1 - Move %c to %c\n", n, with, to);
      global += 2;
      return;
   }
   
   if (n == 2)
   {
      printf("hi");
      global++;
   }
   
   cyclicHanoi(n-1, from, to, with);
   
   printf("%d 2 - Move %c to %c\n", n, from, with);
 
   global++;
   cyclicHanoi(n-2, to, with, from);
   
   printf("Move %c to %c\n", with, to);
   global++;
   
   cyclicHanoi(n-1, from, to, with);
}
