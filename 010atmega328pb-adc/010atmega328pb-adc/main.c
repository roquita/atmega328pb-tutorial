#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "terminal.h"

#define ADC_WORKING() ( ( ADCSRA & (1<<ADSC) ) != 0)

	//ADSC = 1  -> conversion
	//ADSC = 0 ->  complete
	
int main(void)
{
	terminal_init();
	
	// enable adc
	ADCSRA |= (1<<ADEN); 
	
	// internal 1.1v ref
	ADMUX |= ( (1<<REFS1) | (1<<REFS0) );
	
	// set adjust (right)
	ADMUX &= ~(1<<ADLAR);
	
	// prescaler(4) for fadc 	
	ADCSRA &= ~(1<<ADPS2); 
	ADCSRA |= (1<<ADPS1);
	ADCSRA &= ~(1<<ADPS0);
	
	// lectura simple
	
	while (1)
	{
		
		ADMUX |= 2; // select channel 2
		ADCSRA |= (1<<ADSC); // start convertion
		while(ADC_WORKING()); // wait convertion
		uint16_t reading = ADCL + (ADCH<<8); // read convertion for right adjust
		double volts = (reading * 1.1)/1024;
		terminal_printFmt("reading:%i || volts:%.3f\n\r",reading, volts);
		_delay_ms(1000);
		
	}
}

// -lprintf_flt