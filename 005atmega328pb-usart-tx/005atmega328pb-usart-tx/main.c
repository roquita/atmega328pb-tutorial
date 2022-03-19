#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>
#define UDRE0_IS_FULL ((UCSR0A & (1<<UDRE0)) == 0)
// USART0
void configUsart0();
void printChar(char c);
void print_string(char* string);
void printfmt(const char* fmt, ...);
int main(void)
{
	configUsart0();
	int variable = 0 ; 
	while (1)
	{
		//printChar('t');
		//print_string("hola mundo usart0\n\r");
		printfmt("variable = %i \n\r", variable);
		variable++;
		_delay_ms(1000);
	}
}

void configUsart0(){
UBRR0 = 103; //9600baus at 16MHz, doubled speed
UCSR0B |= ( (1<<RXEN0)|(1<<TXEN0));//rx en, tx en
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