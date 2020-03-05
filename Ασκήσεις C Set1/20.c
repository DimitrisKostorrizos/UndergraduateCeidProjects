#include <stdio.h>

int main()
{
int pin,choice;
unsigned long available_money=100,new_deposit,new_withdraw;
do 
{
printf("Enter your pin.\n");
scanf("%d",&pin);
printf("Wrong pin.\n");
}while (pin!=2014);
printf("1) Διαθέσιμο υπόλοιπο\n2) Κατάθεση μετρητών\n3) Ανάληψη μετρητών\n4) Έξοδος\n");
scanf("%d",&choice);
switch (choice)
{
case 1:
printf("Your available balance is %lu.\n",available_money);
break;
case 2:
printf("How much cash do you want deposit?\n");
scanf("%lu",&new_deposit);
available_money+=new_deposit;
break;
case 3:
do
{
printf("How much cash do you want to withdraw?\n");
scanf("%d",&new_withdraw);
if ((new_withdraw%20)!=0)
{
printf("The withdraw number has to be a multiple of 20.\n");
}
else
{
if  (new_withdraw>available_money)
{
printf("Your account does not contain enough money.\nPlease enter another withdraw amount.\n");
}
}
}while((new_withdraw%20)!=0 || new_withdraw>available_money);
available_money-=new_withdraw;
printf("Your new available balance is %lu.\n",available_money);
break;
case 4:
printf("Exiting....\n");
break;
}
return 0;
}

