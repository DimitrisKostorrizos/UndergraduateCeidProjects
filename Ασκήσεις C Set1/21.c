#include "stdio.h"

int main()
{
	int customer_code, sms, time;
	float total_cost, fpa;
	printf("Insert your customer code,your talk time is seconds and your sms number.\n");
	scanf("%d%d%d", &customer_code, &sms, &time);
	total_cost = 1.23*(12 + sms*0.14 + 0.02*time);
	fpa = 0.23*(12 + sms*0.14 + 0.02*time);
	printf("Customer code  time\tSMS\tFPA\t\t|\tTOTAL\n%d\t\t%d\t%d\t%f\t|\t%f\n", customer_code,time,sms,fpa,total_cost);
	return 0;
}
