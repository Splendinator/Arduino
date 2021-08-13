#include "ArduinoModuleUSARTTransmit.h"

#include "Utils.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void ArduinoModuleUSARTTransmit::Setup()
{
	const unsigned int finalRate = (int)((MAIN_CLOCK_RATE / ((unsigned long long)baud * 16ull))) - 1;

	// Set baud rate
	UBRR0H = (unsigned char)(finalRate >> 8);
	UBRR0L = (unsigned char)(finalRate);

	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Set frame format: 8data, 2stop bit
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);

	UCSR0B |= (1 << 6); // Turn on USART transmit complete interrupt

	///RegisterCallback(USART_TX_vect_num, (void*)&ArduinoModuleUSARTTransmit::OnMessageSent);
}

void ArduinoModuleUSARTTransmit::Loop()
{

}

void ArduinoModuleUSARTTransmit::AddMessage(char* pMessage)
{
	bool bStartSendingMessage = dataBuffer[readIndex] == '\0';

	int messageIndex = 0;
	while (pMessage[messageIndex] != '\0')
	{
		dataBuffer[writeIndex] = pMessage[messageIndex];
		IncrementIndex(writeIndex);
		++messageIndex;
	}
	dataBuffer[writeIndex] = '\n';
	IncrementIndex(writeIndex);
	dataBuffer[writeIndex] = '\0';

	if (bStartSendingMessage)
	{
		OnMessageSent();
	}	
}

void ArduinoModuleUSARTTransmit::OnMessageSent()
{
	if (dataBuffer[readIndex] == '\0')
	{
		// No data, do nothing
		return;
	}

	UDR0 = dataBuffer[readIndex]; // Send next byte
	IncrementIndex(readIndex);
}

void ArduinoModuleUSARTTransmit::IncrementIndex(int& index)
{
	++index;
	index %= GetBufferSize();
}
