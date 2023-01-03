#pragma once

#include "operation.h"

class opAddIrregPoly: public operation {
public:
	opAddIrregPoly(controller* pCont);
	virtual ~opAddIrregPoly() override;
	virtual bool Execute() override;
};
