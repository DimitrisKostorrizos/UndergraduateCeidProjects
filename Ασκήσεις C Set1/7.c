#include "stdio.h"





int main()
{

	float f;

	double d;

	printf("Insert a double number.\n");

	scanf("%lf", &d);

	f = (float)d;

	printf("%0.12f\n",d);

	printf("%0.12f\n",f);

    return 0;

}
