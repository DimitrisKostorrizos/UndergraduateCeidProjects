#include "stdio.h"

#include "math.h"



int main()
{

	int n, i=1, sum=0;

	printf("Give an integer.\n");

	scanf("%d", &n);

	for (i = 1;i <= n;i++)

	{

		sum = sum + pow(i, 3);

	}

	printf("%d\n", sum);

	i = 1;

	sum = 0;

	while (i != n+1)

	{

		sum = sum + pow(i, 3);

		i++;

	}

	printf("%d\n", sum);

	i = 1;

	sum = 0;

	do

	{

		sum = sum + pow(i, 3);

		i++;

	} 

	while (i != n+1);

	printf("%d\n", sum);

	i = 1;

	sum = 0;

	for (i = 1; i <= n; i++)

	{

		sum = sum + pow(i, i);

	}

	printf("%d\n", sum);

	i = 1;

	sum = 0;

	while (i != n + 1)

	{

		sum = sum + pow(i, i);

		i++;

	}

	printf("%d\n", sum);

	i = 1;

	sum = 0;

	do

	{

		sum = sum + pow(i, i);

		i++;

	} while (i != n + 1);

	printf("%d\n", sum);

    return 0;
}
