////////////////////////////////
// Id: rome9162
//
// Quick Sort
///////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Quicksort(int**, int, int, int);
int HoarePartition(int**, int, int, int);
void printSubArray(int**, int, int, int);
void printArray();

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      printf("Must input integers\n");
   }
   else
   {
      //int intArr[]; 
      //int size = argc - 1;
      int *intArr = malloc(sizeof(int)*(argc));
      int size = argc;
      //int intArr[] = {5, 2, 3, 4};
      //int size = 4;
      int i;
      for(i = 1; i < argc; i++)
      {
         intArr[i] = atoi(argv[i]);
      }
      Quicksort(&intArr, size - 1, 1, size - 1);
      printSubArray(&intArr, size - 1, 1, size - 1);
      //printSubArray(&intArr, size, 1, size);
   }
   return 0;
}

void Quicksort(int **array, int size, int l, int r)
{
   if (l < r)
   {
      printf("Here");
      printArray(array, size);
      int s = HoarePartition(array, size, l, r);
      Quicksort(array, size, l, s - 1);
      Quicksort(array, size, s + 1, r);
      printSubArray(array, size, l, r);
   }
}

int HoarePartition(int **array, int size, int l, int r)
{
   int p = (*array)[l]; 
   
   int temp;
   
   int i = l;
   int j = r + 1;
   
   //printArray(array, size);
   do {
      do {
         i++;
      } while((*array)[i] < p);
      do {
         --j;
      } while((*array)[j] > p);
 
      temp = (*array)[i];
      (*array)[i] = (*array)[j];
      (*array)[j] = temp;

      //printf("i (after swap): %d ", array[i]);
      //printf("j (after swap): %d ", array[j]);
   
   } while(i < j);
  
   //printArray(array, size);
 
   temp = (*array)[i];
   (*array)[i] = (*array)[j];
   (*array)[j] = temp;

   temp = (*array)[l];
   (*array)[l] = (*array)[j];
   (*array)[j] = temp; 
 
   return j;
}

void printSubArray(int **array, int size, int l, int r)
{
   int i;
   //printf("[");
   for(i = 1; i < l; i++)
   {
      printf("%d ", (*array)[i]);
   }
   printf("[");
   for(i = l; i < r; i++)
   {
      printf("%d ", (*array)[i]);
   }
   printf("%d] ", (*array)[i]);
   for(i = r + 1; i <= size; i++)
   {
      printf(" %d", (*array)[i]);
   }
   printf(" \n");
}

void printArray(int **array, int size)
{
   int i;
   for(i = 1; i < size; i++)
   {
      printf("%d ", (*array)[i]);
   }
   printf("\n");
}
