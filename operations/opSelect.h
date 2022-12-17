#pragma once
#include "operation.h"

class Select : public operation
{
public:
	Select(controller* pCont);
	virtual ~Select();
	virtual bool Execute();
};