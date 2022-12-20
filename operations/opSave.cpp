#include "opSave.h"
#include "opPrompt.h"

#include <filesystem>
#include <fstream>

opSave::opSave(controller* pCont) : operation(pCont)
{
}

opSave::~opSave() = default;

bool opSave::Execute()
{
	GUI* pUI = pControl->GetUI();

	Graph const* graph = pControl->getGraph();
	auto prompt = opPrompt(pControl, "Enter file name");
	prompt.Execute();
	string name = format("save/{}_gf.txt", prompt.response());

	if (name == "_gf.txt")
		return false;

	while (filesystem::exists(name))
	{
		prompt = opPrompt(pControl, "File already exists: Do you want to override it? (y/n)");
		prompt.Execute();
		while (prompt.isYes() == -1) {
			prompt = opPrompt(pControl, "Bad Input: try again");
			prompt.Execute();
		}
		if (prompt.isYes())
			break;
		prompt = opPrompt(pControl, "Enter another name");
		prompt.Execute();
		name = format("save/{}_gf.txt", prompt.response());
	}

	if (!filesystem::exists("save/"))
		filesystem::create_directory("save/");

	ofstream file;
	file.open(name);

	file << pUI->getCrntDrawColor().hex() << ' ' << pUI->getCrntFillColor().hex() << ' ' << pUI->getIsfilled() << ' ' << pUI->getCrntPenWidth() << endl << graph->GetShapeList().size() << endl;

	for (const shape* shape : graph->GetShapeList())
		file << shape->Serialize() << endl;

	file.close();

	pUI->PrintMessage("Save Complete!");

	return false;
}
