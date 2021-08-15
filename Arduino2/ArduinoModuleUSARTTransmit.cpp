#include "ArduinoModuleUSARTTransmit.h"

#include <avr/interrupt.h>

/*static*/ void ArduinoModuleUSARTTransmit::USARTCallback(ArduinoModuleUSARTTransmit* pThis)
{
	pThis->OnMessageSent();
}

void ArduinoModuleUSARTTransmit::Setup()
{
	ArduinoModuleUSARTBase::Setup();

	UCSR0B |= (1 << TXEN0); // Enable transmitting
	UCSR0B |= (1 << 6); // Turn on USART transmit complete interrupt

	RegisterCallback(USART_TX_vect_num, &ArduinoModuleUSARTTransmit::USARTCallback);
}

void ArduinoModuleUSARTTransmit::Loop()
{

}

void ArduinoModuleUSARTTransmit::AddMessage(char* pMessage)
{
	const bool bStartSendingMessage = dataBuffer[readIndex] == '\0';

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
