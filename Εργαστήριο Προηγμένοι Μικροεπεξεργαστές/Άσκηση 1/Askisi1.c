#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <header.h>
#define PIOA_ID 2
#define TC0_ID 17
#define BUT_IDLE 0

#define BUT_PRESSED 1
#define BUT_RELEASED 2
#define LED_IDLE 0
#define LED_FLASHING 1
void FIQ_handler(void);
PIO* pioa = NULL;
AIC* aic = NULL;
TC* tc = NULL;
unsigned int button_state = BUT_IDLE;
unsigned int led_state = LED_IDLE;
unsigned int tmp;
int main( int argc, const char* argv[] )
{
	unsigned int gen;
	STARTUP;
	tc->Channel_0.RC = 8192;
	tc->Channel_0.CMR = 2084;
	tc->Channel_0.IDR = 0xFF;
	tc->Channel_0.IER = 0x10;
	aic->FFER = (1<<PIOA_ID) | (1<<TC0_ID);
	aic->IECR = (1<<PIOA_ID) | (1<<TC0_ID);
	pioa->PUER = 0x01;
	pioa->ODR = 0x01;
	pioa->CODR = 0x02;
	pioa->OER = 0x02;
	gen = pioa->ISR;
	pioa->PER = 0x03;
	gen = tc->Channel_0.SR;
	aic->ICCR = (1<<PIOA_ID)|(1<<TC0_ID);
	pioa->IER = 0x01;
	while( (tmp = getchar()) != 'e')
	{
	}
	aic->IDCR = (1<<PIOA_ID) | (1<<TC0_ID);
	tc->Channel_0.CCR = 0x02;
	CLEANUP;
	return 0;
}

void FIQ_handler(void)
{
	unsigned int data_in = 0;
	unsigned int fiq = 0;
	unsigned int data_out;
	fiq = aic->IPR; 
	if( fiq & (1<<PIOA_ID) )
	{
		data_in = pioa->ISR;
		aic->ICCR = (1<<PIOA_ID);
		data_in = pioa->PDSR;
		if( data_in & 0x01 )
		{
			if(button_state == BUT_IDLE)
			{
				button_state = BUT_PRESSED;
				if( led_state == LED_IDLE )
				{
					tc->Channel_0.CCR = 0x05;
					led_state = LED_FLASHING;
				}
				else
				{
					tc->Channel_0.CCR = 0x02;
					led_state = LED_IDLE;
				}
			}
		}
		else
		{
			if(button_state == BUT_PRESSED)
				button_state = BUT_IDLE;
		}
	}
	if( fiq & (1<<TC0_ID) )
	{
		data_out = tc->Channel_0.SR;
		aic->ICCR = (1<<TC0_ID);
		data_out = pioa->ODSR;
		pioa->SODR = data_out & 0x02;
		pioa->CODR = data_out & 0x02;
		tc->Channel_0.CCR = 0x05;
	}
}