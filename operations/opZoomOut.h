#pragma once
#include "operation.h"
class opZoomOut:
	public operation {
public:
	explicit opZoomOut(controller* pCont);
	~opZoomOut() override;
	bool Execute() override;
};
