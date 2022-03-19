#include <avr/io.h>
#include <avr/eeprom.h>

int miVariable EEMEM = 0xAB;

void printChar(char c){
	UDR0 = c;
	while( (UCSR0A & (1<<UDRE0)) == 0);
}
int main(void)
{	UBRR0 = 103; //9600baus at 16MHz
	UCSR0B |= ( (1<<RXEN0)|(1<<TXEN0));//rx en, tx en	 
	
	int data = eeprom_read_byte((uint8_t*)&miVariable); printChar(data);
		
	eeprom_update_byte((uint8_t*)&miVariable, 0xDE);	
	
	data = eeprom_read_byte((uint8_t*)&miVariable); printChar(data);	
	while (1)
	{}
}

