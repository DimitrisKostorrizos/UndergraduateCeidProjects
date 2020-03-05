#include "stdio.h"





int main()

{

	int highest_common_factor=0,x,y;

	printf("Insert the 2 integers.\n");

	scanf("%d%d", &x, &y);

	if (x >= y)

	{

		if (x%y == 0)

		{

			highest_common_factor = y;

		}

		else

		{

			x = x%y;

		}

	}

		else

		{

		if (y%x == 0)

			{

				highest_common_factor = x;

			}

			else

			{

				y = y%x;

			}

		}

	printf("The highest_common_factor of %d and %d is %d.\n", x, y, highest_common_factor);

	return 0;

}
