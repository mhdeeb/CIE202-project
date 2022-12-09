#include "IrregPoly.h"

IrregPoly::IrregPoly(GfxInfo shapeGfxInfo) : shape(shapeGfxInfo) {}

const int* IrregPoly::getXpoints() const
{
	return &xpoints[0];
}

const int* IrregPoly::getYpoints() const
{
	return &ypoints[0];
}

void IrregPoly::addPoint(const Point &point)
{
	xpoints.push_back(point.x);
	ypoints.push_back(point.y);
}

Point IrregPoly::getPoint(int index)
{
	if (index < 0)
		index = getSize() + index;
	return { xpoints[index], ypoints[index] };
}

int IrregPoly::getSize() const
{
	return xpoints.size();
}

IrregPoly::~IrregPoly() {
	xpoints.clear();
	ypoints.clear();
}

void IrregPoly::Draw(GUI* pUI) const {
	pUI->DrawIrregPoly(this);
}
