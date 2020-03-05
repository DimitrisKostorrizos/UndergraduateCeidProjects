#include <stdio.h>

int main()
{
int digit1, digit2, digit3, digit4, digit5, integer, reversed_integer,temp;
	do
	{
		printf("Insert an integer that is positive and has 5 digits.\n");
		scanf("%d", &integer);
		temp = integer;
		digit5 = integer / 10000;
		integer = integer % 10000;
			digit4 = integer / 1000;
			integer = integer % 1000;
			digit3 = integer / 100;
			integer = integer % 100;
			digit2 = integer / 10;
			integer = integer % 10;
			digit1 = integer;
			reversed_integer = digit1 * 10000 + digit2 * 1000 + digit3 * 100 + digit4 * 10 + digit5;
	} while (temp<10000 || temp>99999);
	printf("The new integer is the %d.\n", reversed_integer);
    return 0;
}
