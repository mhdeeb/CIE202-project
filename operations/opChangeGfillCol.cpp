#include"opChangeGfillCol.h"
#include"opColorPalette.h"


opChangeGfillCol::opChangeGfillCol(controller* pCont) :operation(pCont)
{}
opChangeGfillCol::~opChangeGfillCol()
{}
void opChangeGfillCol::Execute() {
	GUI* pUI = pControl->GetUI();
	Graph* graph = pControl->getGraph();
	opColorPalette(pControl).Execute();
	pUI->setFillColor(pUI->getSelectedColor(), true);
}