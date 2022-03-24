#include <avr/io.h>
#include "terminal.h"
#include <avr/interrupt.h>

int main(void)
{
	terminal_init(); // 9600 bps at 16MHz
	
	// INT 1
	EICRA |= ( (1<<ISC11) | (1<<ISC10)  );
	EIFR &= ~(1<<INTF1);
	EIMSK |= (1<<INT1);
	
	// INT 0
	EICRA |= ( (1<<ISC01) | (1<<ISC00)  ); // config
	EIFR &= ~(1<<INTF0); // resset flag
	EIMSK |= (1<<INT0); // enable interrupt
	
	sei();
	while (1)
	{
	}
}

ISR(INT1_vect){
	terminal_printString("hello from INT1_vect \n\r");	
}


ISR(INT0_vect){
	terminal_printString("hello from INT0_vect \n\r");	
}
