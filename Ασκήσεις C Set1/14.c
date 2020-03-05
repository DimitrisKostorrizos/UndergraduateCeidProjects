#include <stdio.h>
#include <math.h>

int main()
{
	int n,sum=0;
	do 
	{
		printf ("Insert an integer that is positve and less than 10.\n");
		scanf("%d", &n);
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
		if (n>0)
		{
			sum = sum + pow(4 * n, 2);
			n--;
		}
	} while (n < 0 || n > 10);
printf("The result of the representation:4^2+8^2+...(4*n)^2 is equal with %d.\n",sum);
    return 0;
}
