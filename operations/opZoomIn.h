#pragma once
#include "operation.h"
class opZoomIn:
	public operation {
public:
	explicit opZoomIn(controller* pCont);
	~opZoomIn() override;
	bool Execute() override;
};
