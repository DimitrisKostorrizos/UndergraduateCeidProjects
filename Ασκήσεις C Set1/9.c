#include "stdio.h"



int main()

{

	float Fahrenheit_temperature, Celsius_temperature;

	printf("Insert the Fahrenheit temperature number.\n");

	scanf("%f",&Fahrenheit_temperature);

	Celsius_temperature = (float) 5 / 9 * (Fahrenheit_temperature - 32);

	printf("The Celsius temperature number is %f.\n", Celsius_temperature);

    return 0;

}
