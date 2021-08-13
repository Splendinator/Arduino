#pragma once

namespace DomMain
{
	void RegisterCallback(int vecNum, void* pCaller, void (*callback)(void*));
}
