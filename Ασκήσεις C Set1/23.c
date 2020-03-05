#include "stdio.h"


int main()

{

	int N1, N2, N3, N4, max1, max2, sum;

	printf("Insert 4 integers.\n");

	scanf("%d%d%d%d", &N1, &N2, &N3, &N4);

	max1 = (N1 >= N2) ? N1 : N2;

	max1 = (max1 >= N3) ? max1 : N3;

	max1 = (max1 >= N4) ? max1 : N4;

	max2 = (max1!= N1 && N1 > N2) ? N1 : (N2 != max1) ? N2:N1;

	max2 = (max1!=max2 && max2 > N3) ? max2 : (N3 != max1) ? N3:max2;

	max2 = (max1!=max2 && max2 > N4) ? max2 : (N4 != max1) ? N4:max2;

	sum = max1 + max2;

	printf("The maximum sum of %d and %d is %d.\n", max2, max1, sum);

    return 0;

}
