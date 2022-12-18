#include "opSave.h"
#include "opPrompt.h"

#include <filesystem>
#include <fstream>

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
	opPrompt prompt = opPrompt(pControl, "Enter file location");
	prompt.Execute();
	string path = prompt.response();

	while (filesystem::exists(path))
	{
		prompt = opPrompt(pControl, "File already exists: Do you want to override it? (y/n)");
		prompt.Execute();
		while (prompt.isYes() == -1) {
			prompt = opPrompt(pControl, "Bad Input: try again");
			prompt.Execute();
		}
		if (prompt.isYes())
			break;
		prompt = opPrompt(pControl, "Enter another file");
		prompt.Execute();
		path = prompt.response();
	}

	ofstream file;
	file.open(path);

	file << pUI->getCrntDrawColor().hex() << ' ' << pUI->getCrntFillColor().hex() << ' ' << pUI->getIsfilled() << ' ' << pUI->getCrntPenWidth() << endl << graph->GetShapeList().size() << endl;

	for (auto shape : graph->GetShapeList())
		file << shape->Serialize() << endl;

	file.close();

	pUI->PrintMessage("Save Complete!");

	return false;
}
