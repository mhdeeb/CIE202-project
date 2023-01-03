#pragma once

#include "operation.h"

class opAddTri: public operation {
public:
	opAddTri(controller* pCont);
	virtual ~opAddTri() override;
	virtual bool Execute() override;
};
