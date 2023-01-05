#include "opPrompt.h"
#include <filesystem>

opPrompt::opPrompt(controller* pCont, const string& prompt): operation(pCont), prompt(prompt), Response("") {}

opPrompt::~opPrompt() = default;

string opPrompt::response() const {
	return Response;
}

int opPrompt::isYes() const {
	string result = Response;
	std::ranges::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return tolower(c); });
	if (result == "yes" || result == "y")
		return true;
	if (result == "no" || result == "n")
		return false;
	return -1;
}

bool opPrompt::Execute() {
	GUI* pUI = pControl->GetUI();
	Response = pUI->GetString(prompt);
	return false;
}