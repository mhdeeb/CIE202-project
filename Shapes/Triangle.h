#pragma once

#include "IrregPoly.h"

class Triangle : public IrregPoly
{
public:
	Triangle(GfxInfo shapeGfxInfo);
	virtual ~Triangle();
	virtual void Draw(GUI* pUI) const;
	static Triangle* Load(string data);
};
