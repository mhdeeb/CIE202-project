#pragma once
#include "operation.h"
class opResize :
	public operation
{
public:
	explicit opResize(controller* pCont);
	~opResize() override;
	bool Execute() override;
};

