#include "stdio.h"



int main()

{

	int index,n, times_of_appearence=1,max_times=0;

	float previous_number, current_number, key_number;

	printf("How many clauses does this sequence has?\n");

	scanf("%d", &n);

	printf("Insert the first clause of the sequence.\n");

	scanf("%f", &previous_number);

	for (index = 2; index <= n; index++)

	{

		printf("Insert the %d clause of the sequence.\n", index);

		scanf("%f", &current_number);

		if (current_number == previous_number)

		{

			times_of_appearence++;

			previous_number = current_number;

		}

		else

		{

			if (max_times <= times_of_appearence)

			{

				max_times = times_of_appearence;

				times_of_appearence = 0;

				key_number = previous_number;

				previous_number = current_number;

			}

		}

	}

	printf("The clause that appears the most of the times is %f.\n",key_number);

    return 0;

}
