#include"opChangeGfillCol.h"
#include"opColorPalette.h"

opChangeGfillCol::opChangeGfillCol(controller* pCont):operation(pCont) {}
opChangeGfillCol::~opChangeGfillCol() = default;
bool opChangeGfillCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph const* graph = pControl->GetGraph();
	opColorPalette(pControl).Execute();
	pUI->setFillColor(pUI->getSelectedColor(), true);
	for (auto shape : graph->getSelectedShapes())
		shape->setFillColor(pUI->getSelectedColor(), true);
	graph->Refresh(pUI);
	return false;
}