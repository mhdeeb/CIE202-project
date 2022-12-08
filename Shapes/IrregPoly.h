#pragma once

#include "Shape.h"

class IrregPoly : public shape
{
private:
	vector<int> xpoints, ypoints;
	int size;
public:
	IrregPoly(vector<int>, vector<int>, GfxInfo);
	const int* getXpoints() const;
	const int* getYpoints() const;
	int getSize() const;
	virtual ~IrregPoly();
	virtual void Draw(GUI*) const;
};
