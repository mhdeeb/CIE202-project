#pragma once
#include "operation.h"
class opLoad: public operation {
public:
	opLoad(controller* pCont);
	virtual ~opLoad() override;
	virtual bool Execute() override;
};
