#pragma once

#include "Shape.h"

class IrregPoly : public shape
{
private:
	vector<int> xpoints, ypoints;
public:
	IrregPoly(vector<int>, vector<int>, GfxInfo);
	virtual ~IrregPoly();
	virtual void Draw(GUI*) const;
};

