#include "stdio.h"

#include "math.h"



int main()

{

	float a, b, c, d, x1, x2;

	printf("Insert the rates of the trinomial.\n");

	scanf("%f%f%f", &a, &b, &c);

	d = pow(b, 2) - 4 * a * c;

	if (d > 0)

	{

		x1 = (-b + sqrt(d)) /( 2 * a);

		x2 = (-b - sqrt(d)) /( 2 * a);

		printf("The trinomial is (%f)*x^2 + (%f)*x +(%f) and its solutions are x1=%f and x2=%f.\n",a,b,c,x1,x2);

	}

	else

	{

		if (d == 0)

		{

			x1 =(float) -b/(a*2);

				printf("The trinomial is (%f)*x^2 + (%f)*x +(%f) and its double solution is x1=x2=%f.\n", a, b, c,x1);

		}

		else

		{

			printf("The trinomial is (%f)*x^2 + (%f)*x +(%f) but there aren't any real solutions.\n", a, b, c);
		}

	}

	return 0;

}
