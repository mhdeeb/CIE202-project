#pragma once

#include "operation.h"
#include "..\shapes\IrregPoly.h"
#include "..\controller.h"

class opAddIrregPoly : public operation
{
public:
	opAddIrregPoly(controller* pCont);
	virtual ~opAddIrregPoly();
	virtual void Execute();
};

