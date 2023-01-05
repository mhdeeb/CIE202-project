#pragma once

#include "operation.h"

//Add Rectangle operation class
class opAddRect: public operation {
public:
	explicit opAddRect(controller* pCont);
	~opAddRect() override;

	//Add rectangle to the controller
	bool Execute() override;
};
