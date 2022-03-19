/*
* 004atmega328pb-internal-eeprom.c
*
* Created: 3/16/2022 3:44:55 PM
* Author : bill_
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <stdarg.h>
#include <stdio.h>

void configUsart0();
void printChar(char c);
void print_string(char* string);
void printfmt(const char* fmt, ...);

typedef struct{
	int edad;
	char nombre[10];
}persona_t;

EEMEM char caracter = 'A';
EEMEM char string[] = "hola mundo12345";
EEMEM persona_t persona = {
	.edad = 32,
	.nombre = "pedrito",
};


int main(void)
{
	configUsart0();
	while (1)
	{
		// leer byte
		char lectura_byte = eeprom_read_byte((uint8_t*)&caracter);
		printfmt("lectura_byte: %c\n\r", lectura_byte);
		
		// escribir byte
		eeprom_write_byte((uint8_t*)&caracter, lectura_byte + 1);
		
		// leer string
		//char lectura_string[50];
		//eeprom_read_block(lectura_string, string, 15);
		//printfmt("lectura_string: \"%s\"\n\r",lectura_string);
		
		// escribir string
		//eeprom_write_block("avr here yei!", string, 14);
		
		// leer struct		
		/*
		int lectura_int = (int)eeprom_read_word((uint16_t*)&persona.edad);
		char lectura_string[50];
		eeprom_read_block(lectura_string, persona.nombre, 8);
		printfmt("PERSONA:\n\r"
			"\tedad:%i\n\r"
			"\tnombre:\"%s\"\n\r",
			lectura_int, lectura_string);
		*/
		
		// escribir struct
		//eeprom_write_word((uint16_t*)&persona.edad, lectura_int + 1);
		//eeprom_write_block("juan", persona.nombre, 5);		
		
		_delay_ms(1000);
	}
}

void configUsart0(){
	UBRR0 = 103; //9600baus at 16MHz
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