#include "opLoad.h"
#include "opPrompt.h"

#include <filesystem>
#include <fstream>

opLoad::opLoad(controller* pCont) : operation(pCont)
{
}

opLoad::~opLoad()
{
}

bool opLoad::Execute()
{
	GUI* pUI = pControl->GetUI();

	Graph* graph = pControl->getGraph();
	opPrompt prompt = opPrompt(pControl, "Enter file location:");
	prompt.Execute();
	string path = prompt.response();

	while (!filesystem::exists(path))
	{
		prompt = opPrompt(pControl, "File not found: Do you want to try again? (y/n)");
		prompt.Execute();
		while (prompt.isYes() == -1) {
			prompt = opPrompt(pControl, "Bad Input: try again");
			prompt.Execute();
		}
		if (!prompt.isYes())
			break;
		prompt = opPrompt(pControl, "Enter another file");
		prompt.Execute();
		path = prompt.response();
	}

	ifstream file;
	file.open(path);

	string data, drawColor, fillColor;
	int isFilled, drawWidth, shapeCount;
	file >> drawColor >> fillColor >> isFilled >> drawWidth >> shapeCount;
	pUI->setDrawColor(drawColor);
	pUI->setFillColor(fillColor, isFilled);
	pUI->setPenWidth(drawWidth);
	getline(file, data);
	graph->Clear();
	while (getline(file, data))
		graph->Addshape(GUI::ParseShape(data));
	file.close();

	pUI->PrintMessage("Graph Loaded!");

	return false;
}
