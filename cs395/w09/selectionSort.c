////////////////////////////////
// Id: rome9162
//
// Selection Sort
///////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SelectionSort(int[], int);
void printArray();

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      printf("Must input integers\n");
   }
   else
   {
      int intArr[argc - 1]; 
      int size = argc - 1;
      int i;
      for(i = 0; i < argc - 1; i++)
      {
         intArr[i] = atoi(argv[i+1]);
      }

      SelectionSort(intArr, size);
   }
   return 0;
}

void SelectionSort(int array[], int size)
{
   printArray(array, size);
   
   int i;
   int j;
   int min;
   for(i = 0; i <= size - 2; i++)
   {
      min = i;
      for(j = i + 1; j <= size - 1; j++)
      {
         if (array[j] < array[min])
            min = j;
      }
      int temp = array[i];
      array[i] = array[min];
      array[min] = temp;
      printArray(array, size);
   }
}

void printArray(int array[], int size)
{
   int i;
   for(i = 0; i < size; i++)
   {
      printf("%d ", array[i]);
   }
   printf("\n");
}
