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

int opPrompt::isYes() const {
	string result = Response;
	transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return tolower(c); });
	if (result == "yes" || result == "y")
		return true;
	if (result == "no" || result == "n")
		return false;
	return -1;
}

bool opPrompt::Execute()
{
	GUI* pUI = pControl->GetUI();
	Response = pUI->GetSrting(prompt);
	return false;
}
