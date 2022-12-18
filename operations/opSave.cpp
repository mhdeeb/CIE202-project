#include "opSave.h"
#include "opPrompt.h"
#include <filesystem>

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
	opPrompt prompt = opPrompt(pControl, "Enter file location:");
	prompt.Execute();
	string path = prompt.response();
	
	if (filesystem::exists(path))
	{
		opPrompt prompt = opPrompt(pControl, "File already exists: you want to override it? (y/n)");
		path = prompt.response();
	}

	pUI->getWindow();

	return false;
}
