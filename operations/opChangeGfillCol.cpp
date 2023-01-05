#include"opChangeGfillCol.h"
#include"opColorPalette.h"

opChangeGfillCol::opChangeGfillCol(controller* pCont):operation(pCont) {}
opChangeGfillCol::~opChangeGfillCol() {}
bool opChangeGfillCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	opColorPalette(pControl).Execute();
	pUI->setFillColor(pUI->getSelectedColor(), true);
	for (auto shape : graph->getSelectedShapes())
		shape->setFillColor(pUI->getSelectedColor(), true);
	return false;
}