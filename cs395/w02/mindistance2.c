/*********************************************
 * Id: rome9162
 *
 * This program finds the minimum distance between any two number given as input
 **********************************************/
#include <stdio.h>
#include <stdlib.h>

//This is the only function in the program, and the for loops determine the minimum distance
int min(int, int, int, int);

int main(int argc, char *argv[])
{
   int dif = 0;
	
   if(argc < 3)
   {
      printf("Must have more than one number\n");
   }
   else
   {
      int start = 1;
      int i;
      int j;
      for(i = 1; i < argc; i++)
      {
         for(j = i+1; j < argc; j++)
         {
            dif = min(atoi(argv[i]), atoi(argv[j]), start, dif);
            start = 0;
         }
      }
      printf("%d\n",dif);
   }
   return 0;
}

//This function determines if the two numbers given have the minimum distance out of the given array
int min(int numLeft, int numRight, int start, int dif)
{
   if(numRight != 1)
   {
      if(start == 1)
      {
         return abs(numLeft - numRight);
      }
      else
      {
         if(abs(numLeft - numRight) < dif)
         {
            return abs(numLeft - numRight);
         }
      }
   }
   return dif;
}
