/*********************************************
 * Id: rome9162
 *
 * Horspool's algorithm
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET 128
#define TABLE_ROW_LENGTH 16
#define MIN_WRITEABLE 32


void ShiftTable(char[], int, int**);
void printShiftTable(int table[]);
int HorspoolMatching(char[], int, char[], int, int[], int, int**);

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      printf("Must include a pattern and a string\n");
   }
   else
   {
      int *Table;
      Table = (int*)malloc(sizeof(int) * (MAX_ALPHABET - MIN_WRITEABLE));

      int needleSize = strlen(argv[1]);
      int haystackSize = strlen(argv[2]);

      char needle[needleSize];
      char haystack[haystackSize];

      int matches[haystackSize];
      
      strcpy(needle, argv[1]);
      strcpy(haystack, argv[2]);

      ShiftTable(needle, needleSize, &Table);
      HorspoolMatching(needle, needleSize, haystack, haystackSize, matches, haystackSize, &Table);
      //printf("%s\n", needle);
      //printf("%s\n", haystack);
   }

   return 0;
}

//This function creates the shift table for the horspool's algorithm
void ShiftTable(char needle[], int m, int **Table)
{
   int i;
   for (i = 0; i <= MAX_ALPHABET - MIN_WRITEABLE; i++)
   {
      (*Table)[i] = m;
   }
   for (i = 0; i <= m - 2; i++)
   {
      (*Table)[needle[i] - MIN_WRITEABLE] = m - 1 - i;
   }
   printShiftTable(*Table);
}

//This function performs the pattern shifts
int HorspoolMatching(char needle[], int m, char haystack[], int n, int matches[], int matchNum, int **Table)
{
   int j = 0;
   //Table = ShiftTable(needle, m, &Table);//generate Table of shifts
   printf("%s\n", haystack);
   int i = m - 1;//position of the pattes right end
   while(i <= n - 1)
   {
      int k = 0;//number of matched characters
      while (k <= m - 1 && needle[m - 1 - k] == haystack[i - k])
      {
         k = k + 1;
      }
      if (k == m)
      {
         printf("%*s%s---found\n", i-m+1,"", needle);
         matches[j++] = i - m + 1;// Except for your code, do not return. Start looking for the next occurance from here.
         matches[j] = -1;
      }
      else
      {
         printf("%*s%s\n", i - m + 1, "", needle);
      }
      i = i + (*Table)[haystack[i] - MIN_WRITEABLE];
   }
   printf("Matches found at locations:");
   j = 0;
   while(matches[j] != -1)
   {
      printf(" %d", matches[j++]);
   }
   printf("\n");
   return -1;
}

//This function prints the shift table
void printShiftTable(int table[])
{
   int i, start;
   for(start = MIN_WRITEABLE; start < MAX_ALPHABET; start+=TABLE_ROW_LENGTH)
   {
      for(i = start; i < start+TABLE_ROW_LENGTH; i++)
      {
         printf("%c\t", i);
      }
      printf("\n");

      for(i = start; i < start+TABLE_ROW_LENGTH; i++)
      {
         printf("%d\t", table[i - MIN_WRITEABLE]);
      }
      printf("\n\n");

   }
}
