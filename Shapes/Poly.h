#pragma once
#include "IrregPoly.h"
#include "../GUI/GUI.h"
class RegPoly : public IrregPoly
{
public:
	RegPoly(GfxInfo);
	virtual ~RegPoly() override;
	virtual void Draw(GUI*) const override;
};
