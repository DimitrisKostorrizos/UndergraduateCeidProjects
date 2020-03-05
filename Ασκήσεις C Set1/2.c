#include "stdio.h"



int main()

{

	int index;

	for (index = 1; index <= 100; index++)

	{

		printf("%d\t",index);

		if (index % 10 == 0)

		{

			printf("\n");

		}

	}

    return 0;

}
