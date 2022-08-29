#include <stdio.h>

void sumavg(double intArr[])
{
        double sum = 0;

        for(int i = 0; i < 8; i++)
        {
                sum += intArr[i];
        }

        printf("Sum: ");
        printf("%f\n", sum);
        printf("Average: ");
        printf("%f\n\n", sum/8);

}
