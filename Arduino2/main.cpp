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

/**
 * Arduino Modules
 */
ArduinoModuleUSARTTransmit moduleUSARTTransmit(/*baudRate =*/9600);
ArduionoModuleTemp moduleTemp;
ArduinoModuleBase* pArduinoModules[] { &moduleUSARTTransmit, &moduleTemp };

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

void DomMain::PrintMessage(char* pMessage)
{
	moduleUSARTTransmit.AddMessage(pMessage);
}
