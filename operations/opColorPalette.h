#pragma once

#include "operation.h"

class opColorPalette : public operation
{
public:
	opColorPalette(controller*);
	virtual ~opColorPalette();
	virtual void Execute();
};
