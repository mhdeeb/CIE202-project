#include "opExit.h"
#include "opSave.h"
#include "opPrompt.h"

opExit::opExit(controller* pCont) : operation(pCont)
{}

opExit::~opExit()
{}

bool opExit::Execute()
{
	GUI* pUI = pControl->GetUI();
	opPrompt prompt = opPrompt(pControl, "Do you want to save before you exit? y/n");
	prompt.Execute();
	if (prompt.isYes())
		opSave(pControl).Execute();
	else
		return false;
	Graph* graph = pControl->getGraph();
	pUI->getWindow();
	pControl->close();
	return false;
}
