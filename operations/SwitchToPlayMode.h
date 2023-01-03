#pragma once
#include "operation.h"

class SwitchToPlayMode: public operation {
public:
	SwitchToPlayMode(controller* pCont);
	virtual ~SwitchToPlayMode();
	virtual bool Execute();
};