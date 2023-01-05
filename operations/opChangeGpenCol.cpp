#include"opChangeGpenCol.h"
#include"opColorPalette.h"

opChangeGpenCol::opChangeGpenCol(controller* pCont):operation(pCont) {}
opChangeGpenCol::~opChangeGpenCol() = default;
bool opChangeGpenCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph const* graph = pControl->GetGraph();
	opColorPalette(pControl).Execute();
	pUI->setDrawColor(pUI->getSelectedColor());
	for (auto shape : graph->getSelectedShapes())
		shape->setDrawColor(pUI->getSelectedColor());
	graph->Refresh(pUI);
	return false;
}