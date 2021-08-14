#pragma once

namespace DomVectorUtils
{
	// Register a callback from a specific vector number (see interrupt table in docs for numbers)
	// Will call pCallback(pCaller) when the 'vecNum' interrupt is received
	void RegisterCallback(int vecNum, void* pCaller, void (*pCallback)(void*));
}
