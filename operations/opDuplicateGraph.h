#pragma once
#include "operation.h"

class opDuplicateGraph: public operation {
public:
	explicit opDuplicateGraph(controller* pCont);
	~opDuplicateGraph() override;
	bool Execute() override;
};