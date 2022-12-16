#pragma once

#include "operation.h"

class opAddRegPoly : public operation
{
public:
	opAddRegPoly(controller* pCont);
	virtual ~opAddRegPoly();
	virtual void Execute();
};
