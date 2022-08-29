/********************************
 * Id: rome9162
 *
 * Compare sort
 ********************************/

#include <stdio.h>
#include <stdlib.h>

void multiplication(int, int);

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      printf("Must include 2 integers\n");
   }
   else
   {
      multiplication(atoi(argv[1]), atoi(argv[2]));
   }

   return 0;
}

//This function performs russian peasant multiplication on n and m
void multiplication(int n, int m)
{
   int sum = 0;
   while(n != 0)
   {
      if (n % 2 == 0)
      {
         printf("%6d %6d\n", n, m);
      }
      else
      {
         printf("%6d %6d %6d\n", n, m, m);
         sum += m;
      }

      n /= 2;
      m *= 2;
   }

   printf("%20s\n", "------");
   printf("%20d\n", sum);
}
