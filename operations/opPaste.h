#pragma once

#include "operation.h"

class opPaste: public operation {
public:
	opPaste(controller*);
	virtual ~opPaste() override;
	virtual bool Execute() override;
};
