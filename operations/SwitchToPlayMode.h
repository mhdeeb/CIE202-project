#pragma once
#include "operation.h"

class SwitchToPlayMode: public operation {
public:
	explicit SwitchToPlayMode(controller* pCont);
	~SwitchToPlayMode() override;
	bool Execute() override;
};