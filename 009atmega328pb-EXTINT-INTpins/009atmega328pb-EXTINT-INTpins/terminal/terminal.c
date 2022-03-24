#include "terminal.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>

void terminal_init(){
	UBRR0 = 103; //9600baus at 16MHz, doubled speed:  UBRR = [fosc/(16*baud)] - 1
	UCSR0B |=  1<<TXEN0;//rx en, tx en
}

void terminal_printChar(char c){
	UDR0 = c;
	while( (UCSR0A & (1<<UDRE0)) == 0);
}

void terminal_printString(char* string){
	while( *string != 0){
		terminal_printChar(*string);
		string++;
	}
}

void terminal_printFmt(const char* fmt, ...){
	char buffer[100];

	va_list args;
	va_start(args,fmt);
	vsprintf(buffer, fmt, args);
	terminal_printString(buffer);
	va_end(args);
}
