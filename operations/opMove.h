#pragma once
#include "operation.h"
class opMove:
	public operation {
public:
	explicit opMove(controller* pCont);
	~opMove() override;
	bool Execute() override;
};
