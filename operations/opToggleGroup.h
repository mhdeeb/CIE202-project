#pragma once
#include "operation.h"
class opToggleGroup:
	public operation {
public:
	explicit opToggleGroup(controller* pCont);
	~opToggleGroup() override;
	bool Execute() override;
};
