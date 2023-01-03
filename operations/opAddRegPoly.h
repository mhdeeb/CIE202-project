#pragma once

#include "operation.h"

class opAddRegPoly: public operation {
public:
	opAddRegPoly(controller* pCont);
	virtual ~opAddRegPoly() override;
	virtual bool Execute() override;
};
