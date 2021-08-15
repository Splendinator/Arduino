#include "ArduionoModuleUSARTRecieve.h"

#include "main.h"

#include <avr/io.h>
#include <stdio.h>

/*static*/ void ArduionoModuleUSARTRecieve::OnUSARTRecieveInterrupt(ArduionoModuleUSARTRecieve* pThis)
{
	pThis->OnMessageRecieved();
}

void ArduionoModuleUSARTRecieve::Setup()
{
	ArduinoModuleUSARTBase::Setup();

	UCSR0B |= (1 << RXEN0); // Enable recieving

	UCSR0B |= (1 << RXCIE0); // Enable recieving interrupts

	RegisterCallback(USART_RX_vect_num, &ArduionoModuleUSARTRecieve::OnUSARTRecieveInterrupt);
}

void ArduionoModuleUSARTRecieve::OnMessageRecieved()
{
	/// #TODO: If we recieve a '\0' there has been an error. (Maybe look at the falling / rising edge stuff if you get a 0)
	/// If we recieve a '\n' it means the end of the message.
	/// We need to use the above to make this receiver store the whole message and then execute a function based off what we type + params
	
	char pBuffer[16];
	sprintf(pBuffer, "%d(%c)\0", UDR0, UDR0);

	DomMain::PrintMessage(pBuffer);
}
