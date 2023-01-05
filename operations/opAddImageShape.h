#pragma once

#include "operation.h"

class opAddImageShape: public operation {
public:
	explicit opAddImageShape(controller* pCont);
	~opAddImageShape() override;
	bool Execute() override;
};
