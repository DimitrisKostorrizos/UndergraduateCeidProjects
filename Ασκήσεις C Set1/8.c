#include <stdio.h>

#include <math.h>



int main()

{

	float x1, y1, x2, y2, distance;

	printf("Insert the first point's coordinates.\n");

	scanf("%f",&x1);

        scanf("%f",&y1);

	printf("Insert the second point's coordinates.\n");

	scanf("%f",&x2);

        scanf("%f",&y2);

	distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	printf("The distance of those 2 point's is %f.\n", distance);

    return 0;

}
