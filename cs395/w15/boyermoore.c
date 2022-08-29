/*********************************************
 * Id: rome9162
 *
 * Boyer-Moore algorithm
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALPHABET 128
#define TABLE_ROW_LENGTH 16
#define MIN_WRITEABLE 32

void ShiftTable(char[], int, int**);
void printShiftTable(int table[]);
int HorspoolMatching(char[], int, char[], int, int[], int, int**, int**);
void GoodSuffixTable(char[], int, int**);

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

      int *gsuffix;
      gsuffix = (int*)malloc(sizeof(int) * (needleSize));

      char needle[needleSize];
      char haystack[haystackSize];

      int matches[haystackSize];
      
      strcpy(needle, argv[1]);
      strcpy(haystack, argv[2]);

      ShiftTable(needle, needleSize, &Table);
      GoodSuffixTable(needle, needleSize, &gsuffix);
      HorspoolMatching(needle, needleSize, haystack, haystackSize, matches, haystackSize, &Table, &gsuffix);
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

//This function creates the good suffix table
void GoodSuffixTable(char needleF[], int n, int **gsuffix)
{
   // Your code here
   int index, i;  

   /*int *Table;
   Table = (int*)malloc(sizeof(int) * (MAX_ALPHABET - MIN_WRITEABLE));
 
   for (i = 0; i <= MAX_ALPHABET - MIN_WRITEABLE; i++)
   {
      Table[i] = 1;
   }*/

   int nTemp = n;
   //printf("size: %d\n", nTemp);
   n = (2 * n);

   //char needleFull[n];
   char *needleFull;
   needleFull = (char*)malloc(sizeof(char) * (n));

   for(i = 0; i < n; i++)
   {
      if (i < nTemp)
      {
         needleFull[i] = ' ';
      }
      else
      {
         needleFull[i] = needleF[i - nTemp];
      }
   }

   //printf("\n.%s.\n", needleF);
   //printf("\n.%s.\n", needleFull);

   for(index = 1; index < nTemp; index++)
   {
      char *needle;
      needle = (char*)malloc(sizeof(char) * (index));

      char badMatch;
      
      int j;
      int l = 0;
      for(j = index; j > 0; j--)
      {
         needle[l++] = needleFull[n - j];
      }
      badMatch = needleFull[n - index - 1];

      int m = index;
      
      j = 0; //Table = ShiftTable(needle, m, &Table);//generate Table of shifts
      //printf("%s\n", needleFull);
      i = m - 1;//position of the pattes right end
      int dist = nTemp;
      
      //START COPY/////////////////////////////////////////////////////
      while(i < n)
      {
         int k = 0;//number of matched characters
         //printf("Checking against Bad Match: %c\n", needleFull[i - m]);
         if ((i == 0) || (i > 0 && badMatch != needleFull[i - m]))
         {
            while (k <= m - 1 && (needle[m - 1 - k] == needleFull[i - k] || needleFull[i - k] == ' '))
            {
               k = k + 1;
            }
         }
         if (k == m)
         {
            //printf("%*s%s---found\n", i-m+1,"", needle);
            dist = n - i - 1;
            //printf("%*d\n", i-m+1, dist);
         }
         i++;
      }
      (*gsuffix)[index] = dist;
      j = 0;
      //STOP COPY//////////////////////////////////////////////////////
   }
   
   for(i = 1; i < nTemp; i++)
   {  
      printf("%d %*s %d\n", i, nTemp, &needleF[nTemp-i], (*gsuffix)[i]);
   }
}

//This function performs the pattern shifts
int HorspoolMatching(char needle[], int m, char haystack[], int n, int matches[], int matchNum, int **Table, int **gsuffix)
{
   int j = 0; //Table = ShiftTable(needle, m, &Table);//generate Table of shifts
   printf("%s\n", haystack);
   int i = m - 1;//position of the pattes right end
   int minDist = n;
   while(i <= n-1)
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
         minDist = 1;
      }
      else
      {
         if (k > 0)
         {
            printf("%*s%s d1=%d d2=%d\n", i - m + 1, "", needle, (*Table)[haystack[i - k] - MIN_WRITEABLE] - k, (*gsuffix)[k]);
         }
         else
         {
            printf("%*s%s\n", i - m + 1, "", needle);
         }
         
         if((*Table)[haystack[i - k] - MIN_WRITEABLE] - k >= (*gsuffix)[k])
         {
            minDist = (*Table)[haystack[i-k] - MIN_WRITEABLE] - k;
         }
         else
         {
            minDist = (*gsuffix)[k];
         }
      }
      i = i + minDist;
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
