/*********************************************
 * Id: rome9162
 * 
 * This program executes the tower of hanoi algorithm
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void towerOfHanoi(int, char, char, char);

int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      printf("Must have a single integer as input\n");
   }
   else
   {
      towerOfHanoi(atoi(argv[1]), 'A', 'C', 'B');
   }
   return 0;
}

//This function executes the actual tower of hanoi algorithm using recursion
void towerOfHanoi(int num, char from, char to, char other)
{
   if (num == 1)
   {
      printf("MOVE %c TO %c\n", from, to);
      return;
   }
   
   towerOfHanoi(num - 1, from, other, to);
   
   printf("MOVE %c TO %c\n", from, to);
   
   towerOfHanoi(num - 1, other, to, from); 
}
