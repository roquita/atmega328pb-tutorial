#define F_CPU 8000000 // 8MHZ rc internal
#include <util/delay.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "terminal.h"
#include <time.h>

#define TCNT2_NOTREADY ((ASSR & (1<<TCN2UB)) != 0)
#define TCCR2A_NOTREADY ((ASSR & (1<<TCR2AUB)) != 0)
#define TCCR2B_NOTREADY ((ASSR & (1<<TCR2BUB)) != 0)
#define OCR2A_NOTREADY ((ASSR & (1<<OCR2AUB)) != 0)
#define OCR2B_NOTREADY ((ASSR & (1<<OCR2BUB)) != 0)

int main(void)
{
	// led in pb5
	DDRB |= (1<<5);
	PORTB |= (1<<5);
	
	// terminal in usart0
	terminal_init();
	
	// rtc config begin
	_delay_ms(2000);
	
	// PREVENIR INTERRUPCIONES INDECEADAS
	
	TIMSK2 = 0; // disable interrupts
	
	// CAMBIAR FUENTE DE RELOJ
	
	ASSR &= ~(1<<EXCLK); // crystal osc
	//ASSR |= (1<<EXCLK); // external clock on tosc1
	
	ASSR |= (1<<AS2); // set async mode
	
	// RECONFIGURAR TIMER2
	
	TCNT2 = 0; // start value
	TCCR2A = 0; // normal mode
	TCCR2B = 5; // normal mode , prescaler = 128 (256 steps == 1sec)
	OCR2A = 0; // default value
	OCR2B = 0; // default value
	
	while( TCNT2_NOTREADY );
	while( TCCR2A_NOTREADY );
	while( TCCR2B_NOTREADY );
	while( OCR2A_NOTREADY );
	while( OCR2B_NOTREADY );
	
	// REACTIVAR INTERRUPCIONES
	
	TIFR2 = 0; // clean flags
	TIMSK2 |= (1<<TOIE2); // enable tov interrupt	
	
	sei(); // enable global interrupt
	
		
	// CALENDARIO
	
	set_zone(-5*ONE_HOUR);
	set_system_time( 1648075401 - 946684800);
		
	while (1)
	{		
		// CALENDARIO
		
		time_t timestamp = time(NULL);
		char datetime[100] = {0};
		ctime_r( &timestamp, datetime);
		
		terminal_printFmt("ctime_r: %s\n\r", datetime);
		_delay_ms(1000);
		
	}
}

ISR(TIMER2_OVF_vect){
	PORTB ^= (1<<5);
	system_tick();
}
