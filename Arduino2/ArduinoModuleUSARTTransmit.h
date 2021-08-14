#pragma once

#include "ArduinoModuleBase.h"

constexpr int MESSAGE_BUFFER_SIZE = 128;

/** ArduinoModuleUSARTTransmit
*
* This module is used to send data from the microcontroller to the computer using USART transmission.
*/
class ArduinoModuleUSARTTransmit : public ArduinoModuleBase
{
public:
	ArduinoModuleUSARTTransmit(int inBaud) : baud(inBaud) {};

	//~ Begin ArduinoModuleBase Interface
	void Setup() override;
	void Loop() override;
	//~ End ArduinoModuleBase Interface

	void AddMessage(char* pMessage);

	void OnMessageSent();

protected:

	int GetBufferSize() { return MESSAGE_BUFFER_SIZE; }

	void IncrementIndex(int& index);

private:

	static void USARTCallback(ArduinoModuleUSARTTransmit* pThis);

	// Baud rate, set during construction
	int baud;

	// Circle buffer 
	char dataBuffer[MESSAGE_BUFFER_SIZE]; /// #TEMP: This isn't going into .bss
	
	// Our index in the circle buffer that we use to read data
	int readIndex = 0;

	// Our index in the circle buffer that we use to write data
	int writeIndex = 0;
};
