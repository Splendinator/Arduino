#pragma once

#include "ArduinoModuleBase.h"

constexpr int MESSAGE_BUFFER_SIZE = 128;

/** ArduinoModuleUSARTBase
*
* This class is used for #TEMP
*/
class ArduinoModuleUSARTBase : public ArduinoModuleBase
{
public:

	ArduinoModuleUSARTBase(int inBaud) : baud(inBaud) {};

	//~ Begin ArduinoModuleBase Interface
	void Setup() override;;
	//~ End ArduinoModuleBase Interface

protected:

	int GetBufferSize() { return MESSAGE_BUFFER_SIZE; }

	// Increment an index, keeping it within the circle buffer
	void IncrementIndex(int& index);

	// Circle buffer 
	char dataBuffer[MESSAGE_BUFFER_SIZE]; /// #TEMP: This isn't going into .bss

private: 

	// Get final baud rate using "baud" passed through the constructor
	unsigned int GetFinalRate();

	// Baud rate, set during construction
	int baud;

};
