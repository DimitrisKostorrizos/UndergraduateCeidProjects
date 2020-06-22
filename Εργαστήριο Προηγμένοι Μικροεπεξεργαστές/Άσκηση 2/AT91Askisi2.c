#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <header.h>

#define BUT_IDLE 0
#define BUT_PRESSED 1

PIO* pioa = NULL;
AIC* aic = NULL;
TC* tc = NULL;

unsigned int periodCounter = 0;
unsigned int next = 100;
unsigned int status = 0;
unsigned int buttonState = BUT_IDLE;

int main( int argc, const char * argv[] )
{
	int currentNext = 0;
	unsigned int gen;
	
	STARTUP;
	tc->Channel_0.RC = 100;
	tc->Channel_0.CMR = 2084;
	tc->Channel_0.IDR = 0xFF;
	tc->Channel_0.IER = 0x10;
	aic->FFER = (1<<PIOA_ID) | (1<<TC0_ID);
	aic->IECR = (1<<PIOA_ID) | (1<<TC0_ID);
	
	pioa->PUER = 0x200;
	pioa->ODR = 0x200;
	
	pioa->OER = 0xFF;
	pioa->SODR = 0xFF;
	
	gen = pioa->ISR;
	pioa->PER = 0x27F;
	gen = tc->Channel_0.SR;
	aic->ICCR = (1<<PIOA_ID)|(1<<TC0_ID);
	pioa->IER = 0x200;
	
	tc->Channel_0.CCR = 0x02;
	
	// Read until the 'e' character is inserted
	while((tmp=getchar()) != 'e')
	{
		// Reset the current next counter
		if(currentNext > 100)
			currentNext = 0;
		
		if(currentNext < next)
			// Turn off the 7-segment display
			pioa->SODR = 0xFF;
		else
			// Turn on the 7-segment display
			pioa->CODR = 0xFF;
		
		// Increase the current next
		currentNext++;
	}
	
	
}

void FIQ_handler(void)
{
	
	if(fiq & (1<<PIOA_ID))
	{
		data_in = pioa->ISR;
		aic->ICCR = (1<<PIOA_ID);
		data_in = pioa->PDSR;
		
		if(!( data_in & 0x200 ))
		{ 
			if(buttonState == BUT_IDLE)
			{
				buttonState = BUT_PRESSED;
				if(tc->Channel_0.CCR == 0x05)
				{
					tc->Channel_0.CCR = 0x02;
					periodCounter = 0;
				}
				else
				{
					tc->Channel_0.CCR = 0x05;
				}

			}
			else 
			   if(buttonState == BUT_PRESSED)
					buttonState = BUT_IDLE;
		}
	}	
		
		
	if(fiq & (1<<TC0_ID))
	{
		data_out = tc->Channel_0.SR;
		aic->ICCR = (1<<TC0_ID);
		data_out = pioa->ODSR;
		
		periodCounter++;
		
		// If 20 periods have passed
		if(periodCounter == 20)
		{
			// Reset the period counter
			periodCounter = 0;
			
			// Set the flag to count descending
			if(next == 100)
				status = 0;
			else 
			{
				// Set the flag to count ascending
				if(next == 0)
					status = 1;
			}
			
			// Set the next
			if(status)
				next++;
			else
				next--;
		}
		
		// Reset the clock counter
		tc->Channel_0.CCR = 0x05;
	}
}