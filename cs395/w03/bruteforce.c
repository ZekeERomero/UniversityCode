/*********************************************
 * Id: rome9162
 *
 * This program determines 2^n given n as input
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int power(int);

int main(int argc, char *argv[])
{
   if(argc == 2)
   {
      int exp = atoi(argv[1]);
      printf("%d\n",power(exp));
   }
   else
   {
      printf("Must have ONE integer as input\n");
   }

   return 0;
}

//This function executes the given formula
int power(int n)
{
   if(n<1)
   {
      return 1;
   }
   else   
   {
      return power(n-1)+power(n-1);
   }
}
