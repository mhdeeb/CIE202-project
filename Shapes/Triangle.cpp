#include "Triangle.h"

Triangle::Triangle(GfxInfo shapeGfxInfo): IrregPoly(shapeGfxInfo)
{}

Triangle::~Triangle() {}

void Triangle::Draw(GUI* pUI) const {	
	pUI->DrawIrregPoly(this);
}

void Triangle::PrintInfo(GUI* pUI) const {
	pUI->PrintMessage("");
}
