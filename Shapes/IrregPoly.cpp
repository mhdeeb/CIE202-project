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

Point IrregPoly::getPoint(int index) const
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
double IrregPoly::Area(Point p1, Point p2, Point p3 ) {
	return abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
}
bool IrregPoly::isSelected(Point) const {

	return false;
}