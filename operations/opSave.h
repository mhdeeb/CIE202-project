#pragma once
#include "operation.h"
class opSave : public operation
{
public:
	opSave(controller* pCont);
	virtual ~opSave();
	virtual bool Execute();
};
