/*********************************************
 * Id: rome9162
 *
 * This program computes the restriced tower of hanoi problem
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

void restrictedHanoi(int, char, char, char);

int main(int argc, char *argv[])
{
   if (argc < 2)
   {
      printf("Need a single integer input\n");
   }
   else
   {
      restrictedHanoi(atoi(argv[1]), 'A', 'C', 'B');
   }

   return 0;
}

void restrictedHanoi(int n, char from, char to, char with)
{
   if (n == 1)
   {
      printf("Move %c to %c\n", from, with);
      printf("Move %c to %c\n", with, to);
      return;
   }
   restrictedHanoi(n-1, from, to, with);
   printf("Move %c to %c\n", from, with);
   restrictedHanoi(n-1, to, from, with);
   printf("Move %c to %c\n", with, to);
   restrictedHanoi(n-1, from, to, with);
}
