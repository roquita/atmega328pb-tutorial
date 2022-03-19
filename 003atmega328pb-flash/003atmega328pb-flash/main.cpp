#include <avr/io.h>
#include <avr/pgmspace.h>

const uint8_t miVariable PROGMEM  = 0x12;
const char texto[] PROGMEM  = "Cancionero";

int main(void)
{
	while (1)
	{
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