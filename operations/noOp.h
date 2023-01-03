#pragma once
#include "operation.h"

class noOp: public operation {
public:
	noOp(controller* pCont);
	virtual ~noOp() override;
	virtual bool Execute() override;
};
