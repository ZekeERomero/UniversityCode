/*********************************************
 * Id: rome9162
 *
 * Permutations
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char*, char*);
void permute(char*, int, int, int);

int main(int argc, char* argv[])
{
   if (argc == 2)
   {
      int p = atoi(argv[1]);

      char *pList = (char*)malloc(sizeof(char)*p);

      int i;
      for (i = 1; i < p + 1; i++)
      {
         pList[i] = i + '0';
      }

      permute(pList, 0, p, p);
   }

   return 0;
}

//This function swaps the initial and final values
void swap(char *x, char *y)
{
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

//This function performs the permutations on the given list of integers as characters
void permute(char *a, int l, int r, int len)
{
   int i;
   if (l == r && strlen(a) == len)
   {
      printf("%s\n", a);
   }
   else
   {
      for (i = l; i <= r; i++)
      {
         swap((a+l), (a+i));
         permute(a, l+1, r, len);
         swap((a+l), (a+i)); //backtrack
      }
   }
}
