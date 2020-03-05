#include <stdio.h>


int main()
{
	int n,index,sum=0,previous_clause=1,d;
	printf("Insert up to which clause of the Fibonacci sequence you want to calculate.\n");
	scanf("%d",&n);
	if (n > 20)
	{
		n = 20;
		for (index = 1; index <= n; index++)
		{
			printf("%d\t", sum);
			d = sum;
			sum = sum + previous_clause;
			previous_clause = d;
if (index%5==0)
{
printf("\n");
}
		}
	}
	else
	{
		for (index = 1; index <= n; index++)
		{
			printf("%d\t", sum);
			d = sum;
			sum = sum + previous_clause;
			previous_clause = d;
if (index%5==0)
{
printf("\n");
}
		}
	}
printf("\n");
	return 0;
}
