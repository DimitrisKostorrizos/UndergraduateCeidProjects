#include <sys/types.h>      
#include <sys/stat.h>                   
#include <fcntl.h>          
#include <sys/ioctl.h>      
#include <unistd.h>         //At91 libraries
#include <sys/mman.h>       
#include <stdio.h>          
#include <stdlib.h>         
#include <header.h>         

#define off 0				
#define on 1				
#define BUT_IDLE 0			 
#define BUT_PRESSED 1		//Button constants

#define hold 0				
#define game 1				//Led_Constants

PIO* pioa = NULL;	//Δημιουργεία PIO για διαχείρηση της παράλληλης
AIC* aic = NULL;	//Δημιουργεία AIC για διαχείρηση της μονάδας διαχείρησης διακοπών
TC* tc = NULL;		//Δημιουργεία TC για διαχείρηση του ρολογιού

unsigned int player = 0;
unsigned int led = 0;
unsigned int led_state = hold;
unsigned int score1 = 0;
unsigned int score2 = 0;
unsigned int player1ButtonState = BUT_IDLE;
unsigned int btn_n1 = BUT_IDLE;
unsigned int btn_p2 = BUT_IDLE;
unsigned int btn_n2 = BUT_IDLE;
unsigned int player1State = off;
unsigned int p2_state = off;
unsigned int n1_state = off;
unsigned int n2_state = off;
unsigned int player1Counter = 0;
unsigned int p2_counter = 0;
unsigned int n1_counter = 0;
unsigned int n2_counter = 0;
unsigned int win = 0;
unsigned int p1_win = 0;
unsigned int p2_win = 0;

int main( int argc, const char * argv[] )
{
	//SETUP στο arduino
	unsigned int gen;	//Μεταβλήτη για την εκαθάριση των διακοπών
	
	STARTUP;	//Έναρξη του Συστήματος

	tc->Channel_0.RC = 8192;	//Διακοπή ανά 1 sec
	tc->Channel_0.CMR = 2084;	
	tc->Channel_0.IDR = 0xFF;	//Αρχικοποιήση του Ρολόγιου
	tc->Channel_0.IER = 0x10;	
	aic->FFER = (1<<PIOA_ID) | (1<<TC0_ID); 
	aic->IECR = (1<<PIOA_ID) | (1<<TC0_ID);	//Αρχικοποίηση των διακοπών
	
	pioa->PUER = 0x3003; //Τα inputs είναι PULLUP
	pioa->ODR = 0x3003;//Τα bits 0,1 και 12,13 είναι input
	
	pioa->SODR = 0xFFC; //Δυναμικο high στα bits 2-11
	pioa->OER = 0xFFC; //Assign σε output τα bits 2-11
	
	gen = pioa->ISR;//Interupts cleanup στην παράλληλη
	pioa->PER = 0x3FFF; //Tα bits 0-13 σε καταχωρητές γενικού σκοπού
	gen = tc->Channel_0.SR;//Interupts cleanup στο ρολόϊ
	aic->ICCR = (1<<PIOA_ID)|(1<<TC0_ID);//Interupts cleanup στην μονάδα διαχείρησης διακοπών
	pioa->IER = 0x3003;//Interupt στην παράλληλη 0,1 και 12,13
	
	tc->Channel_0.CCR = 0x02; //Αρχικοποίηση του timer στην κατάσταση stop_count
		
	while((tmp=getchar()) != 'e')
	{ //Όσο δεν τερματίζει το πρόγραμμα με 'e'
		if (led_state == hold)
		{//Σε καθε επανάληψη, αν τα τα led ειναι σε κατάσταση hold
			pioa->SODR = 0x3FFF;//Αναψε τα ολα
		}
		else
		{//Αλλιώς
			pioa->CODR = 0x3FFF; //Καθαρισε τα
			pioa->SODR = hex(pow(2,led));//Και αναψε το ledακι στο οποίο βρίσκετε η μπάλα
		}
	}
}

// Handle Interupts
void FIQ_handler(void)
{
	// Parallel Interupt
	if( fiq & (1<<PIOA_ID) )
	{
		// Reset the interupt flag
		data_in = pioa->ISR; 
		
		//Interupts cleanup στην μονάδα διαχείρησης διακοπών
		aic->ICCR = (1<<PIOA_ID);
		
		// Read inputs
		data_in = pioa->PDSR;
		
		// Ignore Interupt
		if (win>0)
		{
			break;
		}
		else if(!( data_in & 0x01 ))
		{
			if(player1Counter == 0)
			{
				if(player1ButtonState == BUT_IDLE)
				{
					player1ButtonState = BUT_PRESSED;
					player1Counter = 6;
					player1State = on;
					
					if(led_state == hold || p1_win = 1)
					{
						led_state = game;	
						player = 2;			
						led = 2;			
						p1_win = 0			
						pioa->CODR = 0x3FFF;
						pioa->SODR = 0x04;
						tc->Channel_0.CCR = 0x05;
					}
				}
			}
			
			if(player1ButtonState == BUT_PRESSED)
			{
				player1ButtonState = BUT_IDLE;
			}
		}
		else if(!( data_in & 0x10 ))
		{
			if(n1_counter == 0)
			{	
				if(btn_n1 == BUT_IDLE)
				{
					btn_n1 = BUT_PRESSED;
					n1_counter = 6;
					n1_state = on;
					
					if(led_state == hold || p1_win = 1)
					{
						led_state = game;
						player = 2;
						led = 2;            
						p1_win = 0			
						pioa->CODR = 0x3FFF;
						pioa->SODR = 0x04; 
						tc->Channel_0.CCR = 0x05;
					}
				}
			}
			
			if(btn_n1 == BUT_PRESSED)
			{
				btn_n1 = BUT_IDLE;
			}
		}
		else if(!( data_in & 0x1000 ))
		{
			if(p2_counter == 0)
			{
				if(btn_p2 == BUT_IDLE)
				{
					btn_p2 = BUT_PRESSED; 
					n1_counter = 6;	
					n1_state = on;
					
					if(led_state == hold || p2_win = 1)
					{
						led_state = game;	
						player = 1;         
						led = 11;          
						p2_win = 0			
						pioa->CODR = 0x3FFF;
						pioa->SODR = 0x800; 
						tc->Channel_0.CCR = 0x05; 
					}
				}
			}
			
			if(btn_p2 == BUT_PRESSED)
			{
				btn_p2 = BUT_IDLE;
			}
		}
		else if(!( data_in & 0x2000 ))
		{
			if(n2_counter == 0)
			{
				if(btn_n2 == BUT_IDLE)
				{ 
					btn_n2 = BUT_PRESSED;
					n2_counter = 6;
					n2_state = on;
					
					if(led_state == hold || p2_win = 1)
					{
						led_state = game;	
						player = 1;         
						led = 11;           
						p2_win = 0			
						pioa->SODR = 0x800; 
						tc->Channel_0.CCR = 0x05;
					}
				}
			}
			
			if(btn_n2 == BUT_PRESSED)
			{
				btn_n2 = BUT_IDLE;
			}
		}		
		
	}
		
	if( fiq & (1<<TC0_ID) )
	{
		data_out = tc->Channel_0.SR;
		aic->ICCR = (1<<TC0_ID);
		data_out = pioa->ODSR;
		
		if(win>0)
		{
			if(p1_win)
			{
				pioa->SODR = 0x04;	
				pioa->CODR = 0x04;	
			}
			
			if(p2_win)
			{		
				pioa->SODR = 0x800;
				pioa->CODR = 0x800;
			}

			win--;
			
			if(!win) 
			{
				break;	
			}
		}
			
		if(player = 1)
		{
			if(led > 2)
			{
				led--;	
			}
			else
			{
				if(player1State || n1_state)
				{
					player = 2;
					if(n1_state)
					{
						tc->Channel_0.RC/=5;
					}

					if(player1State)
					{
						tc->Channel_0.RC = 8192;
					}
					
				}
				else
				{
					score2++;	
					p2_win = 1; 
					win = 6;	
					player1State = off;		 
					p2_state = off;      
					n1_state = off;      
					n2_state = off;      
					player1Counter = 0;      
					p2_counter = 0;      
					n1_counter = 0;      
					n2_counter = 0;      
					player = 0;					
					tc->Channel_0.RC = 8192;
					
					if(score2 >= 3)
					{	
						if(score2 - score1 >= 2)
						{
							led_state = hold;				
							win = 0;                        
							p1_win = 0;                     
							p2_win = 0;                     
							led = 0;                     
							score1 = 0;                     
							score2 = 0;                     
							pioa->SODR = 0x3FFF;            
							tc->Channel_0.CCR = 0x02;       
							break;	//Και τελείωσαε το πρόγραμμα εδω  
						}
					}
				}
			}
		}
		else
		{
			if(led < 11)
			{				
				led++;
			}
			else
			{
				if(p2_state || n2_state)
				{
					player = 1;      
					if(n2_state)   
					{
						tc->Channel_0.RC/=5;	
					}
					if(p2_state)      
					{						
						tc->Channel_0.RC = 8192;
					}
				}
				else
				{
					score1++;
					p1_win = 1; 
					win = 6;    
					player1State = off;	
					p2_state = off; 
					n1_state = off; 
					n2_state = off; 
					player1Counter = 0; 
					p2_counter = 0; 
					n1_counter = 0; 
					n2_counter = 0; 
					player = 0;					
					tc->Channel_0.RC = 8192;    
					if(score1 >= 3)
					{            
						if(score1 - score2 >= 2)
						{	
							led_state = hold;			
							win = 0;                    
							p1_win = 0;                 
							p2_win = 0;					
							led = 0;                  
							score1 = 0;                 
							score2 = 0;                 
							pioa->SODR = 0x3FFF;        
							tc->Channel_0.CCR = 0x02;   
							break;              
						}
					}
				}
			}
		}
		
		
		if(player1Counter>0)
		{				
			player1Counter--;               
			if(player1Counter<4)            
				player1State = off;         
		}                       
        
		if(n1_counter>0)
		{               
			n1_counter--;               
			if(n1_counter<4)            
				n1_state = off;         
		}          
		
		if(p2_counter>0)
		{               
			p2_counter--;               
			if(p2_counter<4)            
				p2_state = off;         
		}            
		
		
		if(n2_counter>0)
		{               
			n2_counter--;               
			if(n2_counter<4)            
				n2_state = off;         
		}                               
		
		pioa->CODR = 0x3FFF;
		pioa->SODR = hex(pow(2,led));
	}
}