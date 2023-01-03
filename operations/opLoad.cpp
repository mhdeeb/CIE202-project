#include "opLoad.h"
#include "opPrompt.h"

#include <filesystem>
#include <fstream>
#include <map>

opLoad::opLoad(controller* pCont): operation(pCont) {}

opLoad::~opLoad() = default;

bool opLoad::Execute() {
	stringstream ss;
	ss << "Select save:\n\n";

	int i = 0;

	string filename;
	map<string, filesystem::path> files;
	for (const auto& save : filesystem::directory_iterator("save/"))
		if ((filename = save.path().filename().string()).ends_with("_gf.txt")) {
			files[to_string(i)] = save.path();
			ss << format("({}) {}\n", i, filename.substr(0, filename.size() - 7));
			i++;
		}

	auto prompt = opPrompt(pControl, ss.str());
	prompt.Execute();
	string response = prompt.response();
	GUI* pUI = pControl->GetUI();

	if (response == "")
		return false;

	if (!files.contains(response)) {
		pUI->PrintMessage("Graph wasn't loaded: bad input");
		return false;
	}

	ifstream file;
	file.open(files[response]);

	string data;
	string drawColor;
	string fillColor;
	int isFilled;
	int drawWidth;
	int shapeCount;
	file >> drawColor >> fillColor >> isFilled >> drawWidth >> shapeCount;
	Graph* graph = pControl->GetGraph();
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