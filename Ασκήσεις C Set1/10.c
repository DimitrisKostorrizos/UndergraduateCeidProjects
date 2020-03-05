#include "stdio.h"

#include "math.h"



int main()

{

	int x, y,sum,max;

	double power,logx,logy;

	printf("Insert the 2 integers.\n");

	scanf("%d%d", &x, &y);

	sum = x + y;

	if (x >= y)

	{

		max = x;

	}

	else

	{

		max = y;

	}

	power = pow(x, y);

	printf("The %d raised to the power of %d is %f.\n", x, y, power);

	if (x>0)

	{

		logx = log10(x);

		printf("The common logarithm (base-10 logarithm) of %d is %f.\n", x, logx);

	}

	else

	{

		printf("It is not defined log(%d) for the first integer.\n", x);

	}

	if (y > 0)

	{

		logy = log10(y);

		printf("The common logarithm (base-10 logarithm) of %d is %f.\n", y, logy);

	}

	else

	{

		printf("It is not defined log(%d) for the second integer.\n", y);

	}

    return 0;

}
