#include <stdio.h>
extern double intArr[8];

void maximum(void)
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
