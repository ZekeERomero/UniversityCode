#include <stdio.h>

void maximum(double intArr[])
{
        double max = intArr[0];

        for(int i = 0; i < 8; i++)
        {
                if(max < intArr[i])
                        max = intArr[i];
        }

        printf("Max: ");
        printf("%f\n", max);

}
