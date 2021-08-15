#pragma once

#include "ArduinoModuleUSARTBase.h"

/** ArduionoModuleTemp
*
* This class is used for #TEMP
*/
class ArduionoModuleUSARTRecieve : public ArduinoModuleUSARTBase
{
public:

	ArduionoModuleUSARTRecieve(int inBaud) : ArduinoModuleUSARTBase(inBaud) {};

	//~ Begin ArduinoModuleBase Interface
	void Setup() override;
	//~ End ArduinoModuleBase Interface

protected:

	void OnMessageRecieved();

private:
	static void OnUSARTRecieveInterrupt(ArduionoModuleUSARTRecieve* pThis);
};
