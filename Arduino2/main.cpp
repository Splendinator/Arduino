/*
* Uno R3 is using the ATmega328P microcontroller:
*
* Datasheet: http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
* Datasheet2: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
* Pinout: https://content.arduino.cc/assets/Pinout-UNOrev3_latest.png
* Header: <avr/iom328p.h> (_AVR_IOM328P_H_)
* 
* USB: https://www.beyondlogic.org/usbnutshell/usb1.shtml && https://www.cypress.com/file/134171/download
* Full Spec: file:///C:/Users/Dominic/AppData/Local/Temp/Temp1_usb_20_20210701.zip/usb_20_20210701/usb_20.pdf
* My Notes: file:///C:/Users/Dominic/Desktop/USB.rtf
*/

#include "main.h"

#include "ArduinoModuleBase.h"
#include "ArduinoModuleUSARTTransmit.h"
#include "ArduionoModuleTemp.h"

#include <avr/interrupt.h>
#include <util/delay.h>

// Arduino Modules
ArduinoModuleUSARTTransmit moduleUSARTTransmit(/*baudRate =*/9600);
ArduionoModuleTemp moduleTemp(&moduleUSARTTransmit);
ArduinoModuleBase* pArduinoModules[] { &moduleUSARTTransmit, &moduleTemp };

// Vector table events (26 vectors)
const int MAX_EVENT_LISTENERS = 3; // Max number of event listeners listening to the same vector
struct ListenerEntry
{
	void(*pCallback)(void*);
	void* pCaller;
};
ListenerEntry eventListeners[26][MAX_EVENT_LISTENERS];

#define PrintMessage(pMessage) moduleUSARTTransmit.AddMessage(pMessage);

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

void DomMain::RegisterCallback(int vecNum, void* pCaller, void (*callback)(void*))
{
	for (int i = 0; i < MAX_EVENT_LISTENERS; ++i)
	{
		ListenerEntry& entry = eventListeners[vecNum][i - 1];
		if (entry.pCallback == nullptr)
		{
			entry.pCallback = callback;
			entry.pCaller = pCaller;
			return;
		}
	}

	PrintMessage("Error: Cannot register callback!");
}

void TestSetup();
void TestLoop();

int main()
{
	for (ArduinoModuleBase* pArduinoModule : pArduinoModules)
	{
		pArduinoModule->Setup();
	}

	sei(); // Set global interupt flag
	
	TestSetup(); /// #TEMP: Temporary function for testing functionality

	for (;;)
	{
		for (ArduinoModuleBase* pArduinoModule : pArduinoModules)
		{
			pArduinoModule->Loop();
		}

		TestLoop();
	}

	return 0;
}

void TestSetup()
{
	
}

void TestLoop()
{

}
