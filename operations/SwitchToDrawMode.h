#pragma once
#include "operation.h"

class SwitchToDrawMode : public operation
{
public:
	SwitchToDrawMode(controller* pCont);
	virtual ~SwitchToDrawMode();
	virtual bool Execute();
};