#include "stdio.h"
#include "math.h"



int main()

{

	int n,a0=1, index;

	float sum= pow(a0, 5) + a0,x,f1,f2;

	printf("Insert the n number.\n");

	scanf("%d", &n);

	index = n;

	for (index=1;index<n;index++)

	{

		sum = pow(sum, 5) + sum;

	}

	printf("The a%d clause is equal to %f.\n",index,sum);

	printf("Insert a real number.\n");

	scanf("%f", &x);

	f1 = pow(x, 5) - pow(x, 3) + 3 * x;

	printf("The value of f1(x)=x^5-x^3+3x for x=%f is equal to %f.\n", x, f1);

	if (x > 0)

	{

		f2 = exp(x) + 4 * log(x) - pow(x, 2);

		printf("The value of f2(x)=e^x+4lnx-x^2 for x=%f is equal to %f.\n", x, f2);

	}

	else

	{

		printf("It is not defined f2(x)=e^x+4lnx-x^2 for x=%.\n", x);

	}

    return 0;

}
