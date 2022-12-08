#include "IrregPoly.h"

IrregPoly::IrregPoly(vector<int> xpoints, vector<int>ypoints, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo), xpoints(xpoints), ypoints(ypoints)
{}

IrregPoly::~IrregPoly() {
	xpoints.clear();
	ypoints.clear();
}

void IrregPoly::Draw(GUI* pUI) const {
	pUI->DrawIrregPoly(xpoints, ypoints, ShpGfxInfo);
}
