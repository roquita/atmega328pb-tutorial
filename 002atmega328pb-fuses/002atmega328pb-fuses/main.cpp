

#include <avr/io.h>
#include <avr/fuse.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/lock.h>
#include <stdio.h>

uint8_t lockData LOCKMEM = 0xE4;

uint8_t fuseData[] FUSEMEM  =
{
	0xE0, // .low (low fuses description)
	0xD9, // .high(high fuses description)
	0xFD, // .extended(extended fuses description)
};

uint8_t var1 EEMEM = 'c';
uint8_t var2  EEMEM = 'd';
uint8_t var3[] EEMEM = "hola mundo";

const char mystring[] PROGMEM= "my_clave";


int main(void)
{
	//uint8_t byte =eeprom_read_byte(&var1);
	//printf( "byte: %u\n", byte );
	while (1)
	{
	}
}

