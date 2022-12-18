#include "opSave.h"

opSave::opSave(controller* pCont) : operation(pCont)
{
}

opSave::~opSave()
{
}

bool opSave::Execute()
{
	GUI* pUI = pControl->GetUI();

	Graph* graph = pControl->getGraph();

	pUI->getWindow();

	return false;
}
