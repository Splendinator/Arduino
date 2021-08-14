#include "ArduinoModuleBase.h"

#include "VectorUtils.h"

void ArduinoModuleBase::RegisterCallback(int vecNum, void* pCallback)
{
	DomVectorUtils::RegisterCallback(vecNum, this, (void(*)(void*))(pCallback));
}
