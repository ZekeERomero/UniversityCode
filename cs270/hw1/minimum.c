#include <stdio.h>
extern double intArr[8];

void minimum(void)
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
