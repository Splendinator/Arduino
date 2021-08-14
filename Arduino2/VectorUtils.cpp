#include "VectorUtils.h"

#include "main.h"

#include <avr/interrupt.h>

/**
 * Vector table events (26 vectors)
 */ 
const int MAX_EVENT_LISTENERS = 4; // Max number of event listeners listening to the same vector
struct ListenerEntry
{
	void(*pCallback)(void*);
	void* pCaller;
};
ListenerEntry eventListeners[26][MAX_EVENT_LISTENERS]; /// #TEMP: This isn't going into .bss

#define RegisterNewVector(vecNum) ISR(_VECTOR(vecNum)) \
{ \
	for(int i = 0; i <  MAX_EVENT_LISTENERS; ++i) \
	{ \
		ListenerEntry& entry = eventListeners[vecNum-1][i]; \
		if (entry.pCallback) \
		{ \
			entry.pCallback(entry.pCaller); \
		} \
	} \
}

RegisterNewVector(1);
RegisterNewVector(2);
RegisterNewVector(3);
RegisterNewVector(4);
RegisterNewVector(5);
RegisterNewVector(6);
RegisterNewVector(7);
RegisterNewVector(8);
RegisterNewVector(9);
RegisterNewVector(10);
RegisterNewVector(11);
RegisterNewVector(12);
RegisterNewVector(13);
RegisterNewVector(14);
RegisterNewVector(15);
RegisterNewVector(16);
RegisterNewVector(17);
RegisterNewVector(18);
RegisterNewVector(19);
RegisterNewVector(20);
RegisterNewVector(21);
RegisterNewVector(22);
RegisterNewVector(23);
RegisterNewVector(24);
RegisterNewVector(25);
RegisterNewVector(26);

void DomVectorUtils::RegisterCallback(int vecNum, void* pCaller, void (*pCallback)(void*))
{
	for (int i = 0; i < MAX_EVENT_LISTENERS; ++i)
	{
		ListenerEntry& entry = eventListeners[vecNum][i - 1];
		if (entry.pCallback == nullptr)
		{
			entry.pCallback = pCallback;
			entry.pCaller = pCaller;
			return;
		}
	}

	DomMain::PrintMessage("DomVectorUtils::RegisterCallback(): Cannot register callback");
}