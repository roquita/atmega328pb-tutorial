#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/atomic.h> // BLOQUES ATOMICOS

// USART0
void configUsart0();
void printChar(char c);
void print_string(char* string);
void printfmt(const char* fmt, ...);

// BUFER CIRCULAR
char bufer[5];
int head = 0;
int tail = 0;
const int max_index = 5-1;
const int min_index = 0;

int bytes_available(){
	if( head>tail ){
		return head-tail;
	}else if ( head < tail)
	{
		return 5 - tail + head;
	}else {
		return 0;
	}
}
char read_byte(){
	char data = bufer[tail];
	tail++;
	if(tail>max_index)
	{
		tail = 0;
	}
	return data;
}

int main(void)
{  
	configUsart0();	
	sei(); // activar interrupcion global
	
    while (1) 
    {
		if( bytes_available()>0 ){
			char v = read_byte();
			printfmt("read_byte : %d \n\r", v);
		}
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
	//printChar(data);
	bufer[head] = data;
	head++;	
	
	if(head > max_index)
	{
		head = 0;
	}
	if(head == tail)
	{
		tail++;
	}
	if(tail > max_index)
	{
		tail = 0;
	}
}


