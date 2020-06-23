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

unsigned int currentPeriod = 0;
unsigned int next = 100;
unsigned int status = 0;
unsigned int fail = 0;
unsigned int success = 1;
unsigned int currentNext = 0;
unsigned int periodCounter = 20;
unsigned int fail_message = 0;
unsigned int buttonState = BUT_IDLE;

int main( int argc, const char * argv[] )
{
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
	
	// If 'e' is pressed, exit
	while((tmp=getchar()) != 'e')
	{
		if(fail_message == 1)
		{
		
			// Reset the error message flag
			fail_message = 0;
			printf("Error: Failure.\n"); 
		}
		
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
	if( fiq & (1<<PIOA_ID) )
	{
		data_in = pioa->ISR;
		aic->ICCR = (1<<PIOA_ID);
		data_in = pioa->PDSR;
		
		if(!( data_in & 0x200 ))
		{
			if(buttonState == BUT_IDLE)
			{
				buttonState = BUT_PRESSED;
				if(tc->Channel_0.CCR == 0x05 || tc->Channel_0.CCR == 0x01)
				{
					// Reset the current period counter
					currentPeriod = 0; 
					if(next == 100)
					{
						fail = 0;
						success	= 1;
						periodCounter--;
					}	
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
			
			// Increase the period counter
			currentPeriod++;
			
			// If the maximum number of periodCounter has been reached
			if(currentPeriod == periodCounter)
			{
			
				currentPeriod = 0;
				
				if(next == 100)
				{
					status = 0;
					fail++;
					
					// If there are 3 fails
					if(fail == 3)
					{
						fail = 0;					
						success = 1;				
						next = 100;					
						status = 0;
						periodCounter = 20;				
						currentNext = 0;				
						tc->Channel_0.CCR = 0x02; 	
						fail_message = 1;		
					}
				}
				else 
				{
					// Start counting ascending
					if(next == 0)
					{
						status = 1;
					}					
				}
				
				// Set the next
				if(status)
					next++;
				else		
					next--;
			}
			else 
				// Reset the success flag
				if(success) 
				{
					success = 0;
				}

			// Reset the clock
			tc->Channel_0.CCR = 0x05;
		}
	}
}