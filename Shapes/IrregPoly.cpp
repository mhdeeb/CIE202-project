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

void IrregPoly::addPoint(const Point& point)
{
	xpoints.push_back(point.x);
	ypoints.push_back(point.y);
}

void IrregPoly::removePoint(int index)
{
	if (index < 0)
		index = getSize() + index;
	xpoints.erase(xpoints.begin() + index);
	ypoints.erase(ypoints.begin() + index);
}

Point IrregPoly::getPoint(int index)
{
	if (index < 0)
		index = getSize() + index;
	return { xpoints[index], ypoints[index] };
}

void IrregPoly::setPoint(Point p, int index)
{
	if (index < 0)
		index = getSize() + index;
	xpoints[index] = p.x;
	ypoints[index] = p.y;
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
bool IrregPoly::isSelected(Point) {

	return false;
}