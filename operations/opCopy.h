#pragma once

#include "operation.h"

class opCopy: public operation {
public:
	opCopy(controller*);
	virtual ~opCopy() override;
	virtual bool Execute() override;
};
