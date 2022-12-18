#pragma once
#include "operation.h"

class Select : public operation
{
public:
	Select(controller* pCont);
	virtual ~Select() override;
	virtual bool Execute() override;
};