////////////////////////////////
// Id: rome9162
//
// Selection Sort
///////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InsertionSort(int[], int);
void printArray(int[], int);
int incr;

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      printf("Must input integers\n");
   }
   else
   {
      incr = 0;
      int intArr[argc - 1]; 
      int size = argc - 1;
      int i;
      for(i = 0; i < argc - 1; i++)
      {
         intArr[i] = atoi(argv[i+1]);
      }

      InsertionSort(intArr, size);
   }
   return 0;
}

void InsertionSort(int array[], int size)
{
   printArray(array, size);
   
   int i;
   int j;
   int v;

   for(i = 1; i <= size - 1; i++)
   {
      v = array[i];
      j = i - 1;
      while(j >= 0 && array[j] > v)
      {
         array[j + 1] = array[j];
         j--;
      }
      array[j + 1] = v;
      printArray(array, size);
   }
}

void printArray(int array[], int size)
{
   int i;
   for(i = 0; i < size; i++)
   {
      printf("%d ", array[i]);
      if (i == incr)
         printf("| ");
   }
   incr++;
   printf("\n");
}
