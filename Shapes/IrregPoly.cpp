#include "IrregPoly.h"

#include <numeric>

IrregPoly::IrregPoly(GfxInfo shapeGfxInfo) : shape(shapeGfxInfo) {}

const int* IrregPoly::getXpoints() const
{
	return &xpoints[0];
}

const int* IrregPoly::getYpoints() const
{
	return &ypoints[0];
}

Point IrregPoly::getCenter() const {
	return center;
}

void IrregPoly::addPoint(const Point& point)
{
	xpoints.push_back(point.x);
	ypoints.push_back(point.y);
	updateCenter();
}

void IrregPoly::removePoint(int index)
{
	if (index < 0)
		index = getSize() + index;
	xpoints.erase(xpoints.begin() + index);
	ypoints.erase(ypoints.begin() + index);
	updateCenter();
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
	updateCenter();
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
double IrregPoly::Area(Point p1, Point p2, Point p3) {
	return abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
}

void IrregPoly::updateCenter() {
	center.x = accumulate(xpoints.cbegin(), xpoints.cend(), 0) / xpoints.size();
	center.y = accumulate(ypoints.cbegin(), ypoints.cend(), 0) / ypoints.size();
}

bool IrregPoly::isSelected(Point p) const {
	double area = 0, testArea = 0;
	int limit = xpoints.size() - 1;
	for (int i = -1; i < limit; ++i)
	{
		area += Area(center, getPoint(i), getPoint(i + 1));
		testArea += Area(p, getPoint(i), getPoint(i + 1));
	}
	return area == testArea;
}