#pragma once

#include "operation.h"

class opAddLine : public operation
{
public:
	opAddLine(controller* pCont);
	virtual ~opAddLine() override;
	virtual bool Execute() override;
};
