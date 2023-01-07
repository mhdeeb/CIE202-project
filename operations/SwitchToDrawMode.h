#pragma once
#include "operation.h"

class SwitchToDrawMode: public operation {
public:
	explicit SwitchToDrawMode(controller* pCont);
	~SwitchToDrawMode() override;
	bool Execute() override;
};