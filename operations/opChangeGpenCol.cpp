#include"opChangeGpenCol.h"
#include"opColorPalette.h"

opChangeGpenCol::opChangeGpenCol(controller* pCont) :operation(pCont)
{}
opChangeGpenCol::~opChangeGpenCol()
{}
bool opChangeGpenCol::Execute() {
	GUI* pUI = pControl->GetUI();
	opColorPalette(pControl).Execute();
	pUI->setDrawColor(pUI->getSelectedColor());
	return false;
}