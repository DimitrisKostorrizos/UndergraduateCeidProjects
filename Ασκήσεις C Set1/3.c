#include "stdio.h"



int main()

{

	int index;

	float grade, average, sum = 0;

	for (index = 1; index <= 10; index++)

	{

		printf("Insert the grade for the subject %d.\n", index);

		scanf("%f", &grade);

		sum = sum + grade;

	}

	average = sum / 10;

	if (average >= 5)

	{

		printf("Success.\n");

	}

	else

	{

		printf("Failure.\n");



	}

    return 0;

}
