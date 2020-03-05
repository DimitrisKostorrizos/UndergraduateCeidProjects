#include "stdio.h"

int main()
{
int choice;
	float Euros, GRD, meters, inches;
	printf("Which conversion do you want to do,1)Euro to GRD or 2)meters to inches?\n");
	scanf("%d", &choice);
	if (choice == 1)
	{
		printf("How many Euros do you want to convert?\n");
		scanf("%f", &Euros);
		GRD = 340.75 * Euros;
		printf("The amount you desire to convert is %f Euros into %f GRD.\n", Euros, GRD);
	}
	if (choice ==2)
	{
		printf("How many meters do you want to convert?\n");
		scanf("%f", &meters);
		inches =0.0254 * meters;
		printf("The amount you desire to convert is %f meters into %f inches.\n", meters, inches);
	}
	return 0;
}
