#pragma once

#include "ArduinoModuleUSARTBase.h"

/** ArduinoModuleUSARTTransmit
*
* This module is used to send data from the microcontroller to the computer using USART transmission.
*/
class ArduinoModuleUSARTTransmit : public ArduinoModuleUSARTBase
{
public:

	ArduinoModuleUSARTTransmit(int inBaud) : ArduinoModuleUSARTBase(inBaud) {};

	//~ Begin ArduinoModuleBase Interface
	void Setup() override;
	void Loop() override;
	//~ End ArduinoModuleBase Interface

	void AddMessage(char* pMessage);

	void OnMessageSent();

private:

	static void USARTCallback(ArduinoModuleUSARTTransmit* pThis);
	
	// Our index in the circle buffer that we use to read data
	int readIndex = 0;

	// Our index in the circle buffer that we use to write data
	int writeIndex = 0;
};
