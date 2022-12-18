#pragma once
#include "operation.h"
class opExit: public operation
{
public:
	opExit(controller* pCont);
	virtual ~opExit() override;
	virtual bool Execute() override;
};
