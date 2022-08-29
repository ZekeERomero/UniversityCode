/*********************************************
 * Id: rome9162
 *
 * Clique finder
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printArray(int**, int);
void array3(int***, int**, int**, int);

int main(int argc, char* argv[])
{
   if(argc > 2 && argc == ((atoi(argv[1])*((atoi(argv[1])-1)))/2) + 2)
   {
      int i, j, size = atoi(argv[1]) + 1;
      
      int **matrix = (int **)malloc(sizeof(int *) * (size));
      int **result = (int **)malloc(sizeof(int *) * (size));
      int **result2 = (int **)malloc(sizeof(int *) * (size));
      for (i = 0; i < size; i++)
      {
         matrix[i] = (int *)malloc(sizeof(int) * (size));
         result[i] = (int *)malloc(sizeof(int) * (size));
         result2[i] = (int *)malloc(sizeof(int) * (size));
      }

      int index = 2;
      for(i = 1; i < size; i++)
      {
         for(j = 1; j < size; j++)
         {
            if ((size - (i - j)) > size)
            {
               matrix[i][j] = atoi(argv[index++]);
            }
            else
            {
               matrix[i][j] = 0;
            }
         }
      }

      index = 2;
      for(j = 1; j < size; j++)
      {
         for(i = 1; i < size; i++)
         {
            if ((size - (i - j)) < size)
            {
               matrix[i][j] = atoi(argv[index++]);
            }
         }
      }

      printArray(matrix, size);

      array3(&result, matrix, matrix, size);
      array3(&result2, result, matrix, size);

      int *resultArr = (int*)malloc(sizeof(int) * size);
      int *valueArr = (int*)malloc(sizeof(int) * size);

      for(i = 1; i < size; i++)
      {
         resultArr[i] = result2[i][i];
         valueArr[i] = 0;
      }

      for(i = 1; i < size; i++)
      {
         for(j = 0; j < size; j++)
         {
            if(resultArr[i] == resultArr[j])
            {
               valueArr[i]++;
            }
         }
      }

      bool found;
      for(i = size - 1; i > 0; i--)
      {
         found = false;
         for(j = 0; j < size; j++)
         {
            if(i == valueArr[j])
            {
               found = true;
            }
         }
         if (found)
         {
            printf("Clique found of size %d\n", i);
            return 0;
         }
         else
         {
            printf("No clique found of size %d\n", i);
         }
      }
   }
   else
   {
      printf("Must input more values\n");
   }

   return 0;
}

//This function prints out any given array 
void printArray(int** matrix, int size)
{
   int i, j;
   for(i = 1; i < size; i++)
   {
      for(j = 1; j < size; j++)
      {
         printf("%d ",matrix[i][j]);
      }
      printf("\n");
   }
}

//This function multiplies matrix1 and matrix2 and places the result in *result
void array3(int*** result, int** matrix1, int** matrix2, int size)
{
   int i, j, m;
   for(j = 1; j < size; j++)
   {
      for(i = 1; i < size; i++)
      {
         int sum = 0;
         for(m = 0; m < size; m++)
         {
            sum += matrix1[i][m] * matrix2[m][j];
         }
         (*result)[j][i] = sum;
      }
   }
}
