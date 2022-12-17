#pragma once
#include "operation.h"
class opChangeGfillCol : public operation
{
public:
	opChangeGfillCol(controller* pCont);
	virtual ~opChangeGfillCol();
	virtual bool Execute();
};