#include "ArduinoModuleUSARTBase.h"

#include "Utils.h"

#include <avr/io.h>

void ArduinoModuleUSARTBase::Setup()
{
	const unsigned int finalRate = GetFinalRate();
	
	// Set baud rate
	UBRR0H = (unsigned char)(finalRate >> 8);
	UBRR0L = (unsigned char)(finalRate);

	// Set frame format: 8data, 2stop bit
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

unsigned int ArduinoModuleUSARTBase::GetFinalRate()
{
	return (int)((MAIN_CLOCK_RATE / ((unsigned long long)baud * 16ull))) - 1;
}

void ArduinoModuleUSARTBase::IncrementIndex(int& index)
{
	++index;
	index %= GetBufferSize();
}
