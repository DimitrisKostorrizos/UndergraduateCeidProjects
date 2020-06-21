#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <header.h>

unsigned int buttonState = BUT_IDLE;//RESET btn

PIO* pioa = NULL;
unsigned int periodCounter = 0;
unsigned int next = 100;
unsigned int countingFlag = 0;


int main(int argc, const char * argv[])
{
	int currentNext = 0;
	unsigned int gen;
	
	STARTUP;
	tc->Channel_0.RC = 100;//Frequency =100 pulses
	tc->Channel_0.CMR = 2084;
	tc->Channel_0.IDR = 0xFF;
	tc->Channel_0.IER = 0x10;
	aic->FFER = (1<<PIOA_ID) | (1<<TC0_ID);
	aic->IECR = (1<<PIOA_ID) | (1<<TC0_ID);
	
	pioa->PUER = 0x200; //PULLUP Inputs
	pioa->ODR = 0x200;//Bit 9 input
	
	pioa->OER = 0xFF; //Bits 0-6 Outpouts
	pioa->SODR = 0xFF;  //Turn on Display
	
	gen = pioa->ISR;//Interupts cleanup
	pioa->PER = 027F; //0-6,9 generic
	gen = tc->Channel_0.SR;//Interupts cleanup
	aic->ICCR = (1<<PIOA_ID)|(1<<TC0_ID);//Interupts cleanup
	pioa->IER = 0x91;//Interupt on 9
	
	tc->Channel_0.CCR = 0x02; //Timer stopped
	
	// Read characters from the keyboard
	while((tmp = getchar()) != 'e')
	{
		// Reset current next to 0
		if(currentNext > 100)
			currentNext = 0;
		
		// If current next is less that next
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
	{// Διακοπές από την παράλληλη
		data_in = pioa->ISR;//Interupt cleanup
		aic->ICCR = (1<<PIOA_ID);//Interupts cleanup
		data_in = pioa->PDSR;//Data inputs read
		
		if(!(data_in & 0x200))
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
		   {
			   if(buttonState == BUT_PRESSED)
			   {
					buttonState = BUT_IDLE;
			   }
		   }
		}
	}	
	
	
	if( fiq & (1<<TC0_ID) ){//Timer Interupts
		data_out = tc->Channel_0.SR;//Interupts cleanup
		aic->ICCR = (1<<TC0_ID);//Interupts cleanup
		data_out = pioa->ODSR;//Data exits read
		
		periodCounter++;
		
		// If 20 periods have passed
		if(periodCounter == 20)
		{
			// Reset the period counter
			periodCounter = 0;
			if(next == 100)
			{	
				// Set the flag to decrease the next
				countingFlag = 0;
			}
			else 
			{
				if(next == 0)
				{
					// Set the flag to increase the next
					countingFlag = 1;
				}
			}
			if(countingFlag)
			{
				// Increase the next
				next++;
			}
			else
			{
				// Decrease the next
				next--;
			}
		}
		
		// Set the channel ccr to 0x05
		tc->Channel_0.CCR = 0x05;
	}
}