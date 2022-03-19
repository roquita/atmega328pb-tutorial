#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>

// USART0
void configUsart0();
void printChar(char c);
void print_string(char* string);
void printfmt(const char* fmt, ...);

int main(void)
{
    /* Replace with your application code */
	configUsart0();	
	sei(); // activar interrupcion global
	
    while (1) 
    {
		/*
		bool data_ready = ( UCSR0A & (1<<RXC0) )!=0;
		if(data_ready){
			char data = UDR0; // leer data
			printChar(data);
		}
		*/
		// tarea 1
		// tarea 2
		// tarea 3 
		// tarea 4
	}
}

void configUsart0(){
	UBRR0 = 103; //9600baus at 16MHz, doubled speed
	UCSR0B |= ( (1<<RXEN0) | (1<<TXEN0) );//rx en, tx en
	UCSR0B |= (1<<RXCIE0); // activar interrupcion rx
}

void printChar(char c){
	UDR0 = c;
	while( (UCSR0A & (1<<UDRE0)) == 0);
}

void print_string(char* string){
	while( *string != 0){
		printChar(*string);
		string++;
	}
}

void printfmt(const char* fmt, ...){
	char buffer[100];

	va_list args;
	va_start(args,fmt);
	vsprintf(buffer, fmt, args);
	print_string(buffer);
	va_end(args);
}


ISR(USART0_RX_vect){
	char data = UDR0; // leer data
	printChar(data);		
}

