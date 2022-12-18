#pragma once

#include "operation.h"

class opAddSquare : public operation
{
public:
	opAddSquare(controller* pCont);
	virtual ~opAddSquare() override;
	virtual bool Execute() override;
};
