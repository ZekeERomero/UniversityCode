#include <stdio.h>

void minimum(double intArr[])
{
        double min = intArr[0];

        for(int i = 0; i < 8; i++)
        {
                if(min > intArr[i])
                        min = intArr[i];
        }

        printf("Max: ");
        printf("%f\n", min);

}
