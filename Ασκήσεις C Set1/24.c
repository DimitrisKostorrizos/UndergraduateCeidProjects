#include "stdio.h"





int main()

{

	int N,digit1,digit2,new_integer;

	printf("Give an integer with 2 digits.\n");

	scanf("%d", &N);

		digit1 = N / 10;

		digit2 = N % 10;

		new_integer = digit1*1000+digit1*100+digit2 * 10 + digit2 * 1;

		printf("The new integer is %d.\n", new_integer);

		return 0;

}
