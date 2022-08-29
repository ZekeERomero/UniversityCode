///////////////////////////////////////
// Id: rome9162
//
// Program that finds patterns in text
///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BruteForceStringMatch(char[], char[]);

int main(int argc, char* argv[])
{
   if (argc < 3)
   {
      printf("Must include two strings\n");
   }
   else
   {
      printf("Matches found at locations:");
      BruteForceStringMatch(argv[2], argv[1]);
   }
   return 0;
}

int BruteForceStringMatch(char text[], char pattern[])
{
   int n = strlen(text);
   int m = strlen(pattern);
   
   int i = 0;
   int j = 0;
   for (i = 0; i <= n - m; i++)
   {
      j = 0;  
      while ((j < m) && (pattern[j] == text[i + j]))
      {
         j++;
      }
      if (j == m)
       printf(" %d",i);
   }
   printf("\n");
   return -1;
}
