#pragma once
#include "operation.h"
class opExit: public operation {
public:
	explicit opExit(controller* pCont);
	~opExit() override = default;
	bool Execute() override;
};
