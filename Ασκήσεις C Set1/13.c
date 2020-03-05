#include "stdio.h"





int main()

{

	int index;

	for (index = 1; index <= 79; index++)

	{

		printf("%c(%d)\t", index+47, index+47);

		if (index%10==0)

		{

			printf("\n");

		}

	}

	printf("\n");

    return 0;

}
