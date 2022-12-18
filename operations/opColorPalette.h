#pragma once

#include "operation.h"

class opColorPalette : public operation
{
public:
	opColorPalette(controller*);
	virtual ~opColorPalette() override;
	virtual bool Execute() override;
};
