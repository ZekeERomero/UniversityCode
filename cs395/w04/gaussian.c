/*********************************************
 * Id: rome9162
 *
 * This program executes gaussian elimination to find the solutions to a set of equations
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

void printMatrix(float**, int, int);

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
      
      float **A;
      int i, j, k;
      int incr = 2;

      A = malloc(rows * sizeof *A);

      for(i = 0; i < rows; i++)
      {
         A[i] = malloc(cols * sizeof *A[i]);
      }

      for(i = 0; i < rows; i++)
      {
         for(j = 0; j < cols; j++)
         {
            A[i][j] = atoi(argv[incr++]);
         }
      }

      printMatrix(A, rows, cols);

      float tempji;

      for(i = 0; i <= rows - 2; i++)
      {
         for(j = i + 1; j <= rows - 1; j++)
         {
            tempji = A[j][i];
            for(k = i; k <= rows; k++)
            {
               A[j][k] = A[j][k] - (A[i][k] * tempji / A[i][i]);
            }
         }
         printMatrix(A, rows, cols);
      }

      for(i = 0; i < rows; i++)
      {
         free(A[i]);
      }
   }
   return 0;
}

//This function prints the matrix
void printMatrix(float **Arr, int rows, int cols)
{
   int i, j;
   for(i = 0; i < rows; i++)
   {
      for(j = 0; j < cols; j++)
      {
         printf("%.2f ", Arr[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}
