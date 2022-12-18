#include "opPrompt.h"
#include <filesystem>

opPrompt::opPrompt(controller* pCont, string prompt) : operation(pCont), prompt(prompt), Response("")
{
}

opPrompt::~opPrompt()
{
}

string opPrompt::response() const {
	return Response;
}

bool opPrompt::Execute()
{
	GUI* pUI = pControl->GetUI();
	Response = pUI->GetSrting(prompt);
	return false;
}
