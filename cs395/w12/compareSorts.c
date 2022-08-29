/********************************
 * Id: rome9162
 *
 * Compare sort 
 ********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

void InsertionSort(int[], int);
void SelectionSort(int[], int);
void Quicksort(int[], int, int, int);
int HoarePartition(int[], int, int, int);

int main()
{
   int startPow = 3;
   int endPow = 5;
   int i;
   int j;
   srand(time(NULL));
   int powerIndex;
   float insertionTime[endPow - startPow + 1];
   double selectionTime[endPow - startPow + 1];
   double quickTime[endPow - startPow + 1];
   for(j = startPow; j <= endPow; j++)
   {
      int power = 10;
      for(powerIndex = 0; powerIndex < j - 1; powerIndex++)
      {
         power *= 10;
      }
      int intArr[power];
      for(i = 0; i < power; i++)
      {
         intArr[i] = rand() % 10;
      }

      struct timeval start, stop;

      gettimeofday(&start, NULL);
      InsertionSort(intArr, power);
      gettimeofday(&stop, NULL);
      insertionTime[j - startPow] = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
      
      gettimeofday(&start, NULL);
      SelectionSort(intArr, power);
      gettimeofday(&stop, NULL);
      selectionTime[j - startPow] = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
      
      gettimeofday(&start, NULL);
      Quicksort(intArr, power, 1, power);
      gettimeofday(&stop, NULL);
      quickTime[j - startPow] = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   }
   printf("//+-----------------------+-----------------+----------------+------------+\n");
   printf("//|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |\n");
   printf("//+-----------------------+-----------------+----------------+------------+\n");
   for(i = startPow; i <= endPow; i++)
   {
      int power = 10;
      for(powerIndex = 0; powerIndex < i - 1; powerIndex++)
      {
         power *= 10;
      }
      printf("//|%*d", 23, power);
      printf("|%*d", 17, (int)selectionTime[i - startPow] + 1);
      printf("|%*d", 16, (int)insertionTime[i - startPow] + 1);
      printf("|%*d|\n", 12, (int)quickTime[i - startPow] + 1);
   }
   printf("//+-----------------------+-----------------+----------------+------------+\n");
   
   return 0;
}

// This function performs an insertion sort
void InsertionSort(int array[], int size)
{
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
   }
}

// This function performs a selection sort
void SelectionSort(int array[], int size)
{
   int i;
   int j;
   int min;
   for(i = 0; i <= size - 2; i++)
   {
      min = i;
      for(j = i + 1; j <= size - 1; j++)
      {
         if (array[j] < array[min])
         {
            min = j;
         }
      }
      int temp = array[i];
      array[i] = array[min];
      array[min] = temp;
   }
}

// This function performs a quick sort
void Quicksort(int array[], int size, int l, int r)
{
   if (l < r)
   {
      int s = HoarePartition(array, size, l, r);
      Quicksort(array, size, l, s - 1);
      Quicksort(array, size, s + 1, r);
   }
}

// This function performs a hoare partition for quick sort
int HoarePartition(int array[], int size, int l, int r)
{
   int p = array[l];

   int temp;

   int i = l;
   int j = r + 1;

   do {
      do {
         i++;
      } while(array[i] < p);
      do {
         --j;
      } while(array[j] > p);

      temp = array[i];
      array[i] = array[j];
      array[j] = temp;

   } while(i < j);

   temp = array[i];
   array[i] = array[j];
   array[j] = temp;

   temp = array[l];
   array[l] = array[j];
   array[j] = temp;

   return j;
}

//+-----------------------+-----------------+----------------+------------+
//|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
//+-----------------------+-----------------+----------------+------------+
//|                   1000|                2|               1|           1|
//|                  10000|              133|              75|           2|
//|                 100000|            13203|            7333|          19|
//+-----------------------+-----------------+----------------+------------+

//+-----------------------+-----------------+----------------+------------+
//|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
//+-----------------------+-----------------+----------------+------------+
//|                   1000|                2|               1|           1|
//|                  10000|              133|              73|           2|
//|                 100000|            13218|            7358|          19|
//+-----------------------+-----------------+----------------+------------+

//+-----------------------+-----------------+----------------+------------+
//|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
//+-----------------------+-----------------+----------------+------------+
//|                   1000|                2|               1|           1|
//|                  10000|              133|              74|           2|
//|                 100000|            13214|            7340|          19|
//+-----------------------+-----------------+----------------+------------+
