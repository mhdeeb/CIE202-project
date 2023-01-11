#include "opLoad.h"
#include "opPrompt.h"

#include <filesystem>
#include <map>

opLoad::opLoad(controller* pCont): operation(pCont) {}

opLoad::~opLoad() = default;

bool opLoad::Execute() {
	GUI* pUI = pControl->GetUI();
	auto [response, files] = pUI->fileSelect("save/", "_gf.txt");
	if (response == "")
		return false;

	if (!files.contains(response)) {
		pUI->PrintMessage("Graph wasn't loaded: bad input");
		return false;
	}

	pControl->GetGraph()->Load(files[response], pUI);
	pUI->PrintMessage("Graph Loaded!");
	return false;
}