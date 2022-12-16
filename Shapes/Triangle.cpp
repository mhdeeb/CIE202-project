#include "Triangle.h"

Triangle::Triangle(GfxInfo shapeGfxInfo): IrregPoly(shapeGfxInfo)
{}

Triangle::~Triangle() {}

void Triangle::Draw(GUI* pUI) const {	
	pUI->DrawIrregPoly(this);
}

bool Triangle::isSelected(Point) const
{
	return false;
}
