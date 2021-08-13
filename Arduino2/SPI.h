#pragma once

void SPISetUp()
{
	/*
	* SPI has 4 pins:
	* SCK - master clock
	* MOSI - Master Out Slave In
	* MISO - Master In Slave Out
	* SS - Set to 0 to be activated, otherwise set to 1 using pull-up resistor (There is one SS line for each slave device)
	*/

	// Step 1 - Set the data direction 
	/* Set MOSI and SCK output, all others input */
	// SCK uses portB5, MOSI uses portPB3. See https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#page=65&zoom=100,45,69
	// 
	DDRB = (1 << PORTB3) | (1 << PORTB5);

	// Step 2 - Set up the SPI control register (SPCR)
	// SPI Control Register: https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#page=140&zoom=100,45,69
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPISendData()
{
	// Step 3 - Set the SPI Data Register with the data we want to send
	SPDR = 'D';

	// Step 4 - Wait for the SPI Status Register's "SPI Interrupt Bit" to get set to 1
	while (SPSR & 1 << SPIF);
}
