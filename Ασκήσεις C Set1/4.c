#include "stdio.h"
#include "math.h"



int main()

{

	int int1, int2, sum, product, difference, abs;

	printf("Insert the first integer.\n");

	scanf("%d", &int1);

	printf("Insert the second integer.\n");

	scanf("%d", &int2);

	sum = int1 + int2;

	product = int1*int2;

	difference = int1 - int2;

	abs = fabs(difference);

	if (product > 0 && product < 10)

	{

		printf("The sum of the 2 integers is %d.\n", sum);

	}

	if (product>100 && product<1000)

	{

		printf("The difference of the 2 integers is %d.\n", abs);

	}
else
{
  printf("Those 2 numbers don't fulfill the requirements.\n");
	}

    return 0;

}
