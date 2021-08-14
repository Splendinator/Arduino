#pragma once

#include "ArduinoModuleBase.h"

class ArduinoModuleUSARTTransmit;

/** ArduionoModuleTemp
*
* This class is used for #TEMP
*/
class ArduionoModuleTemp : public ArduinoModuleBase
{
public:

	//~ Begin ArduinoModuleBase Interface
	void Setup() override;
	void Loop() override;
	//~ End ArduinoModuleBase Interface

protected:
};
