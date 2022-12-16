#include "RegPoly.h"


RegPoly::RegPoly(GfxInfo shapeGfxInfo) : IrregPoly(shapeGfxInfo) {}

RegPoly::~RegPoly() {
	IrregPoly::~IrregPoly();
}

void RegPoly::Draw(GUI* pUI) const {
	pUI->DrawRegPoly(this);
}
