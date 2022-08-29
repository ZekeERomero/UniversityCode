#include <stdio.h>
#include <stdlib.h>

#define MAX_BOARD 50
#define BCEMPTY 10

void printQueue(int[], int, int);
void printGraph(int[MAX_BOARD][MAX_BOARD], int);
void printM(int[][2], int, int);

int main(int argc, char* argv[])
{
   if (argc > 1)
   {
      f
   }
   else
   {
      df
   }
   return 0;
}


void MaximumBipartiteMatching(G)
{
   initialize set M of edges with some valid matching (e.g., the empty set)
   initialize queue Q with all the free vertices in V (in any order)
   while not Empty(Q)
   {
      printQueue(Q)
      w = Front(Q); Dequeue(Q)
      if w is an element of V
      {
         for every vertex u adjacent to w do
         {
            if u is free
            {
               M = M + (w, u)
               v = w
               while v is labeled do
               {
                  u = vertex indicated by v's label; M = M - (v, u)
                  v = vertex indicated by u's label; M = M + (v, u)
               }
               remove all vertex labels
               reinitialize Q with all free vertices in V
               break; //exit the for loop
            }
            else //u is matched
            {
               if (w, u) is not an element of M and u is unlabeled
               {
                  label u with w
                  Enqueue(Q, u)
               }
            }
         }
      }
      else //w is and element of U (and matched)
      {
         label the mate v of w with w
         Enqueue(Q, v)
      }
      printM(M)
   }
   return M
}

// Print the adjacentcy matrix.
void printGraph(int G[MAX_BOARD][MAX_BOARD], int Vverticies)
{
   int i, j;
   for(i=0; i<Vverticies; i++)
   {
      printf("%d ->", i);
      j=0;
      while(G[i][j] != BCEMPTY)
      {
         printf(" %d", G[i][j]);
         j++;
      }
      printf("\n");
   }
}

// Print out the current contents of the queue for debugging
void printQueue(int Queue[], int start, int end)
{
   int i;
   printf("Queue:");
   for(i=start; i<end; i++)
   {
      printf(" %d", Queue[i]);
   }
   printf("\n");
}

// Print out the currenlty found matchings
void printM(int M[][2], int start, int end)
{
   int i;
   for(i=start; i<end; i++)
   {
      printf("\tV%d", M[i][0]);
   }
   printf("\n");

   for(i=start; i<end; i++)
   {
      printf("\t|");
   }
   printf("\n");

   for(i=start; i<end; i++)
   {
      printf("\tU%d", M[i][1]);
   }
   printf("\n");
}
