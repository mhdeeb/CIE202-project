#pragma once
#include "operation.h"

class opChangeGpenCol : public operation
{
public:
	opChangeGpenCol(controller* pCont);
	virtual ~opChangeGpenCol();
	virtual void Execute();
};
