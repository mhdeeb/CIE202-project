#include "opExit.h"
#include "opSave.h"

opExit::opExit(controller* pCont) : operation(pCont)
{}

opExit::~opExit()
{}

bool opExit::Execute()
{
	GUI* pUI = pControl->GetUI();
	string choice = pUI->GetSrting("Do you want to save before you exit? y/n");
	if (choice == "y")
		opSave(pControl).Execute();
	else if (choice != "n")
		return false;
	Graph* graph = pControl->getGraph();
	pUI->getWindow();
	pControl->close();
	return false;
}
