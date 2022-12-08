#include "IrregPoly.h"

IrregPoly::IrregPoly(vector<int> xpoints, vector<int>ypoints, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo), xpoints(xpoints), ypoints(ypoints), size(xpoints.size())
{}

const int* IrregPoly::getXpoints() const
{
	return &xpoints[0];
}

const int* IrregPoly::getYpoints() const
{
	return &ypoints[0];
}

int IrregPoly::getSize() const
{
	return size;
}

IrregPoly::~IrregPoly() {
	xpoints.clear();
	ypoints.clear();
}

void IrregPoly::Draw(GUI* pUI) const {
	pUI->DrawIrregPoly(this);
}
