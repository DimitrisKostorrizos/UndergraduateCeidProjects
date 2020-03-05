#include <stdio.h>


int main()
{
	int index;
	printf("N\tN*2\tN*3\tN*10\t\n");
	for (index = 1; index <= 10; index++)
	{
		printf("%d\t%d\t%d\t%d\t\n", index, index * 2, index * 3,index * 10);
	}
    return 0;
}
