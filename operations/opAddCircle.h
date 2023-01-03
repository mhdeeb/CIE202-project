#pragma once

#include "operation.h"

class opAddCircle: public operation {
public:
	opAddCircle(controller* pCont);
	virtual ~opAddCircle() override;
	virtual bool Execute() override;
};
