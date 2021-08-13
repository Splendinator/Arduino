#include "ArduinoModuleBase.h"

#include "main.h"

void ArduinoModuleBase::RegisterCallback(int vecNum, void* pCallback)
{
	DomMain::RegisterCallback(vecNum, this, (void(*)(void*))(pCallback));
}
