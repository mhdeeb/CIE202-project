#include "Triangle.h"

Triangle::Triangle(GfxInfo shapeGfxInfo): IrregPoly(shapeGfxInfo)
{}

Triangle::~Triangle() {}

void Triangle::Draw(GUI* pUI) const {	
	pUI->DrawIrregPoly(this);
}

bool Triangle::isSelected(Point p) const
{
	double area = Area(getPoint(0), getPoint(1), getPoint(2));

	double area1 = Area(p, getPoint(1), getPoint(2));

	double area2 = Area(p, getPoint(0), getPoint(2));

	double area3 = Area(p, getPoint(0), getPoint(1));

	if (area == area1 + area2 + area3)
		return true;

	else return false;
}
