#pragma once
#include "operation.h"
class opRotate :
    public operation
{
public:
	explicit opRotate(controller* pCont);
	~opRotate() override;
	bool Execute() override;
};

