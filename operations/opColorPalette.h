#pragma once

#include "operation.h"

class opColorPalette: public operation {
private:
	bool lockScreen;
public:
	opColorPalette(controller*, bool lockScreen = true);
	virtual ~opColorPalette() override;
	virtual bool Execute() override;
};
