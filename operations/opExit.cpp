#include "opExit.h"
#include "opSave.h"
#include "opPrompt.h"

opExit::opExit(controller* pCont) : operation(pCont)
{}

opExit::~opExit()
{}

bool opExit::Execute()
{
	auto prompt = opPrompt(pControl, "Do you want to save before you exit? y/n");
	prompt.Execute();
	if (prompt.isYes() == 1)
		opSave(pControl).Execute();
	else if (prompt.isYes() == -1)
		return false;
	pControl->GetUI()->getWindow();
	pControl->close();
	return false;
}
