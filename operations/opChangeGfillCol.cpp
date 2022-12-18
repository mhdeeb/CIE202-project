#include"opChangeGfillCol.h"
#include"opColorPalette.h"


opChangeGfillCol::opChangeGfillCol(controller* pCont) :operation(pCont)
{}
opChangeGfillCol::~opChangeGfillCol()
{}
bool opChangeGfillCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->getGraph();
	opColorPalette(pControl).Execute();
	pUI->setFillColor(pUI->getSelectedColor(), true);
	if (graph->getSelectedShape())
		graph->getSelectedShape()->setFillColor(pUI->getSelectedColor(), true);
	return false;
}