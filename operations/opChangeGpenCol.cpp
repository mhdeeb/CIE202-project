#include"opChangeGpenCol.h"
#include"opColorPalette.h"

opChangeGpenCol::opChangeGpenCol(controller* pCont):operation(pCont) {}
opChangeGpenCol::~opChangeGpenCol() {}
bool opChangeGpenCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	opColorPalette(pControl).Execute();
	pUI->setDrawColor(pUI->getSelectedColor());
	for (auto shape : graph->getSelectedShapes())
		shape->setDrawColor(pUI->getSelectedColor());
	return false;
}