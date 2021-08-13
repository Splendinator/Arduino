#pragma once

/** ArduinoModuleBase
*
* This is the base class for an arduino module.
* It just has an "Init()" and "Loop()" functions that can be overriden
*/
class ArduinoModuleBase
{
public:

	// Ran once at the start
	virtual void Setup() {};

	// Ran as often as possible
	virtual void Loop() {};

protected:

	void RegisterCallback(int vecNum, void* pCallback);

private:

};