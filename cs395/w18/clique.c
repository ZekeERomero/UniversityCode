/*********************************************
 * Id: rome9162
 *
 * This program finds the largest clique in a graph
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
  
#define MAX 100

void printArray(int**, int);
bool is_clique(int**, int*, int);
int max(int, int);
int maxCliques(int**, int**, int, int, int);
void getEdges(int**, int***, int);

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

      index = 0;
      for(j = 1; j < size; j++)
      {
         for(i = 1; i < size; i++)
         {
            if ((size - (i - j)) < size)
            {
               if(matrix[i][j] == 1)
							 {
                  index++;
							 }
            }
         }
      }

      printArray(matrix, size);

      int *store = (int*)malloc(sizeof(int)*MAX);
      int **graph = (int**)malloc(sizeof(int*)*MAX);
      for(i = 0; i < MAX; i++)
      {
         graph[i] = (int*)malloc(sizeof(int)*MAX);
      }
      int *d = (int*)malloc(sizeof(int)*MAX);

      int **edges = (int**)malloc(sizeof(int*)*index);
      for(i = 0; i < MAX; i++)
      {
         edges[i] = (int*)malloc(sizeof(int)*2);
      }
   
      getEdges(matrix, &edges, size);

      for (i = 0; i < index; i++)
      {
         graph[edges[i][0]][edges[i][1]] = 1;
         graph[edges[i][1]][edges[i][0]] = 1;
         d[edges[i][0]]++;
         d[edges[i][1]]++;
      }

      int maxVal = maxCliques(graph, &store, size, 0, 1);

      int temp = size - 1;
      while(temp != maxVal)
      {
         printf("No clique found of size %d\n", temp--);
      }

      printf("Clique found of size %d\n", temp);
   }
   else
   {
      printf("Incorrect input\n");
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
         printf("%d ", matrix[i][j]);
      }
      printf("\n");
   }
}

//This function turns the matrix in a set of edges
void getEdges(int **matrix, int ***edges, int size)
{
   int i, j, index = 0;

   for(i = 1; i < size; i++)
   {
      for(j = 1; j < size; j++)
      {
         if (matrix[i][j] == 1 && (size - (i - j)) > size)
         {
            (*edges)[index][0] = i;
            (*edges)[index++][1] = j;
         }
      }
   }
}

//Function to check if the given set of vertices in store array is a clique or not
bool is_clique(int **graph, int *store, int b)
{
   int i, j;
   for (i = 1; i < b; i++)
   {
      for (j = i + 1; j < b; j++)
      {
         if (graph[store[i]][store[j]] == 0)
         {
            return false;
         }
      }
   }
   return true;
}

//This function returns the max of two values
int max(int a, int b)
{
   if (a > b)
   {
      return a;
   }
   else
   {
      return b;
   }
}

//Function to find all the sizes of maximal cliques
int maxCliques(int **graph, int **store, int n, int i, int l)
{
   int j, max_ = 0;

   for (j = i + 1; j <= n; j++)
   {
      (*store)[l] = j;

      if (is_clique(graph, *store, l + 1))
      {
         max_ = max(max_, l);
         max_ = max(max_, maxCliques(graph, store, n, j, l + 1));
      }
   }
   return max_;
}
