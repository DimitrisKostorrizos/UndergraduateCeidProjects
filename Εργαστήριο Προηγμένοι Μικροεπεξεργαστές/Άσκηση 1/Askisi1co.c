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
// Θέσε την αρχική κατάσταση του κουμπιού σε μη πατημένο
unsigned int button_state = BUT_IDLE;
// Θέσε την αρχική κατάσταση του λαμπακίου σε σβηστό
unsigned int led_state = LED_IDLE;
// Όρισε μια μη απαιτούμενη μεταβλητή tmp
unsigned int tmp;
int main( int argc, const char* argv[] )
{
	unsigned int gen;
	STARTUP; //ΑΡΧΙΚΟΠΟΙΗΣΗ ΣΥΣΤΗΜΑΤΟΣ
	tc->Channel_0.RC = 8192; //ΠΕΡΙΟΔΟΣ 1 ΔΕΥΤΕΡΟΛΕΠΤΟ
	tc->Channel_0.CMR = 2084; // SLOW CLOCK , WAVEFORM , DISABLE CLK ON RC COMPARE
	tc->Channel_0.IDR = 0xFF; //ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ ΟΛΩΝ ΤΩΝ ΔΙΑΚΟΠΩΝ
	tc->Channel_0.IER = 0x10; //ΕΝΕΡΓΟΠΟΙΗΣΗ ΜΟΝΟ ΤΟΥ RC COMPARE
	aic->FFER = (1<<PIOA_ID) | (1<<TC0_ID); //ΟΙ ΔΙΑΚΟΠΕΣ 2 ,17 ΕΙΝΑΙ ΤΥΠΟΥ FIQ
	aic->IECR = (1<<PIOA_ID) | (1<<TC0_ID); //ΕΝΕΡΓΟΠΟΙΗΣΗ ΔΙΑΚΟΠΩΝ : PIOA & TC0
	pioa->PUER = 0x01; //ΕΝΕΡΓΟΠΟΙΗΣΗ ΣΤΗ ΓΡΑΜΜΗ 0 : PULL−UP
	pioa->ODR = 0x01; //ΓΡΑΜΜΗ 0 : ΛΕΙΤΟΥΡΓΙΑ ΕΙΣΟΔΟΥ
	pioa->CODR = 0x02; //ΓΡΑΜΜΗ 1 : ΔΥΝΑΜΙΚΟ ΕΞΟΔΟΥ LOW
	pioa->OER = 0x02; //ΓΡΑΜΜΗ 1 : ΛΕΙΤΟΥΡΓΙΑ ΕΞΟΔΟΥ
	gen = pioa->ISR; // PIOA : ΕΚΚΑΘΑΡΙΣΗ ΑΠΟ ΤΥΧΟΝ ΔΙΑΚΟΠΕΣ
	pioa->PER = 0x03; //ΓΡΑΜΜΕΣ 0 , 1 : ΓΕΝΙΚΟΥ ΣΚΟΠΟΥ
	gen = tc->Channel_0.SR; //TC0 : ΕΚΚΑΘΑΡΙΣΗ ΑΠΟ ΤΥΧΟΝ ΔΙΑΚΟΠΕΣ
	aic->ICCR = (1<<PIOA_ID)|(1<<TC0_ID); // AIC : ΕΚΚΑΘΑΡΙΣΗ ΑΠΟ ΤΥΧΟΝ ΔΙΑΚΟΠΕΣ
	pioa->IER = 0x01; //ΕΝΕΡΓΟΠΟΙΗΣΗ ΔΙΑΚΟΠΩΝ ΣΤΗ ΓΡΑΜΜΗ 0
	// Διάβασε χαρακτήρες από το πληκτρολόγιο μέχρι να εισαχθεί ο χαρακτήρας e...
	while( (tmp = getchar()) != 'e')
	{
	}
	// Εκτέλεσε την διαδικασία τερματισμού όταν εισαχθεί ο χαρακτήρας e
	aic->IDCR = (1<<PIOA_ID) | (1<<TC0_ID); // ΔΙΑΚΟΠΗ ΤΩΝ AIC i n t e r r u p t s
	tc->Channel_0.CCR = 0x02; // ΑΠΕΝΕΡΓΟΠΟΙΗΣΗ ΤΟΥ Time r
	CLEANUP;
	return 0;
}

void FIQ_handler(void)
{
	// Θέσε τον καταχωρητή δεδομένων εισόδου σε 0
	unsigned int data_in = 0;
	// Θέσε την κατάσταση διακοπής σε 0
	unsigned int fiq = 0;
	// Όρισε ένα καταχωρητή δεδομένων  εξ΄δου
	unsigned int data_out;
	fiq = aic->IPR; //ΕΝΤΟΠΙΣΜΟΣ ΠΕΡΙΦΕΡΕΙΑΚΟΥ ΠΟΥ ΠΡΟΚΑΛΕΣΕ ΤΗ ΔΙΑΚΟΠΗ
	if( fiq & (1<<PIOA_ID) )
	{ //ΕΛΕΓΧΟΣ ΓΙΑ PIOA
		data_in = pioa->ISR; //ΕΚΚΑΘΑΡΙΣΗ ΤΗΣ ΠΗΓΗΣ ΤΗΣ ΔΙΑΚΟΠΗΣ
		aic->ICCR = (1<<PIOA_ID); //ΕΚΚΑΘΑΡΙΣΗ ΤΗΣ ΔΙΑΚΟΠΗΣ ΑΠΟ AIC
		data_in = pioa->PDSR; //ΑΝΑΓΝΩΣΗ ΤΙΜΩΝ ΕΙΣΟΔΟΥ
		if( data_in & 0x01 )
		{ //ΔΙΑΚΟΠΤΗΣ ΠΑΤΗΜΕΝΟΣ ;
			if(button_state == BUT_IDLE)
			{
				// Θέσε την κατάσταση του κουμπιού ως πατημένο
				button_state = BUT_PRESSED;
				// Αν το λαμπάκι είναι σβηστό
				if( led_state == LED_IDLE )
				{ //ΑΝ ΔΕΝ ΑΝΑΒΟΣΒΗΝΕΙ
					tc->Channel_0.CCR = 0x05; //ΕΝΑΡΞΗ ΜΕΤΡΗΤΗ					
					// Θέσε την κατάσταση του λαμπακίου ως φωτεινό
					led_state = LED_FLASHING;
				}
				else
				{
					tc->Channel_0.CCR = 0x02; //ΔΙΑΚΟΠΗ ΜΕΤΡΗΤΗ
					// Θέσε την κατάσταση του λαμπακίου ως σβηστό
					led_state = LED_IDLE;
				}
			}
		}
		else
		{				
			// Αν το κουμπί είναι πατημένο
			if(button_state == BUT_PRESSED)				
				// Θέσε την κατάσταση του κουμπιού ως μη πατημένο
				button_state = BUT_IDLE;
		}
	}
	if( fiq & (1<<TC0_ID) )
	{
		data_out = tc->Channel_0.SR;//ΕΚΚΑΘΑΡΙΣΗ ΤΗΣ ΠΗΓΗΣ ΤΗΣ ΔΙΑΚΟΠΗΣ
		aic->ICCR = (1<<TC0_ID); //ΕΚΚΑΘΑΡΙΣΗ ΔΙΑΚΟΠΗΣ ΚΑΙ ΑΠΟ AIC
		data_out = pioa->ODSR; //ΑΝΑΓΝΩΣΗ ΤΙΜΩΝ ΕΞΟΔΟΥ
		// Ενεροποίησε μόνο το δεύτερο bit στον καταχωρητή SODR
		pioa->SODR = data_out & 0x02;
		// Ενεροποίησε μόνο το δεύτερο bit στον καταχωρητή CODR
		pioa->CODR = data_out & 0x02;
		//Διακοπη μετρητή
		tc->Channel_0.CCR = 0x05;
	}
}