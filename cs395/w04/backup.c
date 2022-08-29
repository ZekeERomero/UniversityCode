#include <stdio.h>
#include <stdlib.h>

void printMatrix(float*, int, int);

int main(int argc, char *argv[])
{
   if (argc < 3)
   {
      printf("Need more than 3 inputs\n");
   }
   else
   {
      int rows = atoi(argv[1]);
      int cols = (argc-2)/rows;
      //printf("%d",rows);
      
      float A[rows][cols];
      int rowCounter = 0;
      int colCounter = 0;
      int i, j;
      int incr = 2;

      for(i = 0; i < rows; i++)
      {
         for(j = 0; j < cols; j++)
         {
            A[i][j] = atoi(argv[incr++]);
         }
      }

      for(i = 0; i < rows; i++)
      {
         for(j = 0; j < cols; j++)
         {
            printf("%.2f ",A[i][j]);
         }
         printf("\n");
      }

      printMatrix(A, rows, cols);
   }
   return 0;
}

void printMatrix(float *Arr, int rows, int cols)
{
   int i, j;
   for(i = 0; i < rows; i++)
   {
      for(j = 0; j < cols; j++)
      {
         printf("%d ", Arr[i][j]);
      }
      printf("\n");
   }
}
