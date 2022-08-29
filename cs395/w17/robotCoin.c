/*********************************************
 * Id: rome9162
 *
 * Robot Coin Collector
 ***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int***, int, int);
int RobotCoinCollection(int**, int***, int, int);
int max(int, int);

int main(int argc, char* argv[])
{
   if (argc > 1)
   {
      int i, j, size = atoi(argv[1]) * atoi(argv[2]);
      int ySize = atoi(argv[1]) + 1, xSize = atoi(argv[2]) + 1;
      if (argc - 3 == size)
      {
         int index = 3;
         //char matrix[ySize][xSize];
         
         int **matrix = (int **)malloc(sizeof(int *) * (ySize));
         for (i = 0; i < ySize; i++)
         {
            matrix[i] = (int *)malloc(sizeof(int) * (xSize));
         }

         for(i = 1; i < ySize; i++)
         {
            for(j = 1; j < xSize; j++)
            {
               if (*argv[index] != 'X')
               {
                  matrix[i][j] = atoi(argv[index++]);
               }
               else
               {
                  matrix[i][j] = -1;
                  index++;
               }
            }
         }
         
         printf("Board Inputed:\n");

         printArray(&matrix, xSize, ySize);

         int **result = (int **)malloc(sizeof(int *) * (ySize));
         for (i = 0; i < ySize; i++)
         {
            result[i] = (int *)malloc(sizeof(int) * (xSize));
         }

         int optimalPath = RobotCoinCollection(matrix, &result, xSize, ySize);

         printf("Coin Collecting Table:\n");
         printArray(&result, xSize, ySize);

         printf("The optimal path with this board is: %d\n", optimalPath);
         
         for (i = 0; i < ySize; i++) {
            free(matrix[i]);
            free(result[i]);
         }
         free(matrix);
         free(result);
      }
      else
      {
         printf("Number of inputs must match first input dimensions\n");
      }
   }
   else
   {
      printf("Must include input in the format './a.out a b # # # #...' where a x b is the size of the grid\n");
   }

   return 0;
}

//This function transforms the initial matrix into a best value path
int RobotCoinCollection(int **C, int ***F, int m, int n)
{
   int i, j;

   int optimalPath = 0;
   int temp;

   (*F)[1][1] = C[1][1];
   
   for (j = 2 ; j < m; j++)
   {
      if (C[1][j] != -1 && (*F)[1][j - 1] != -1)
      {
         (*F)[1][j] = (*F)[1][j - 1] + C[1][j];
         temp = (*F)[1][j];
         optimalPath = max(optimalPath, temp);
      }
      else
      {
         (*F)[1][j] = -1;
      }
   }
   //printArray(F, m, n);
   for (i = 2; i < n; i++)
   {
      if (C[i][1] != -1 && (*F)[i - 1][1] != -1)
      {
         (*F)[i][1] = (*F)[i - 1][1] + C[i][1];
         temp = (*F)[i][1];
         optimalPath = max(optimalPath, temp);
      }
      else
      {
         (*F)[i][1] = -1;
      }
      for (j = 2; j < m; j++)
      {
         if (C[i][j] != -1 && ((*F)[i - 1][j] != -1 || (*F)[i][j - 1] != -1))
         {
            (*F)[i][j] = max((*F)[i - 1][j], (*F)[i][j - 1]) + C[i][j];
            temp = (*F)[i][j];
            optimalPath = max(optimalPath, temp);
            // printf("Testing: %d vs %d and got %d from %d\n", (*F)[i - 1][j], (*F)[i][j - 1], (*F)[i][i], C[i][j]);
         }
         else
         {
            (*F)[i][j] = -1;
         }
         //printArray(F, m, n);
      }
   }
   
   for (i = 1 ; i < n; i++)
   {
      for (j = 1; j < m; j++)
      {
         if ((*F)[i][j] == -1)
         {
            (*F)[i][j] = 0;
         }
      }
   }

   return optimalPath;
}

//This function returns the max of two numbers
int max(int x1, int x2)
{
   if (x1 > x2)
   {
      return x1;
   }
   else
   {
      return x2;
   }
}

//This function prints a given array
void printArray(int ***matrix, int xSize, int ySize)
{
   int i, j;
   for(i = 1; i < ySize; i++)
   {
      for(j = 1; j < xSize; j++)
      {
         if ((*matrix)[i][j] != -1)
         {
            printf("%d\t", (*matrix)[i][j]);
         }
         else
         {
            printf("X\t");
         }
      }
      printf("\n");
   }
   printf("\n");
}

