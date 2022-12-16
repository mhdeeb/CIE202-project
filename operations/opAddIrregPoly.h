#pragma once

#include "operation.h"

class opAddIrregPoly : public operation
{
public:
	opAddIrregPoly(controller* pCont);
	virtual ~opAddIrregPoly();
	virtual void Execute();
};
