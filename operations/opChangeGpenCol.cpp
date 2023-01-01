#include"opChangeGpenCol.h"
#include"opColorPalette.h"

opChangeGpenCol::opChangeGpenCol(controller* pCont) :operation(pCont)
{}
opChangeGpenCol::~opChangeGpenCol()
{}
bool opChangeGpenCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->GetGraph();
	opColorPalette(pControl).Execute();
	pUI->setDrawColor(pUI->getSelectedColor());
	if (graph->getSelectedShape())
		graph->getSelectedShape()->setDrawColor(pUI->getSelectedColor());
	return false;
}