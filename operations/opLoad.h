#pragma once
#include "operation.h"
class opLoad : public operation
{
public:
	opLoad(controller* pCont);
	virtual ~opLoad();
	virtual bool Execute();
};
