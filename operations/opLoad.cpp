#include "opLoad.h"
#include "opPrompt.h"

#include <filesystem>
#include <fstream>
#include <map>

opLoad::opLoad(controller* pCont) : operation(pCont)
{
}

opLoad::~opLoad() = default;

bool opLoad::Execute()
{
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
	Graph* graph = pControl->getGraph();
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

//bool opLoad::Execute()
//{
//	GUI* pUI = pControl->GetUI();
//
//	Graph* graph = pControl->getGraph();
//	auto prompt = opPrompt(pControl, "Enter file location:");
//	prompt.Execute();
//	string path = prompt.response();
//
//	if (path == "")
//		return false;
//
//	while (!filesystem::exists(path))
//	{
//		prompt = opPrompt(pControl, "File not found: Do you want to try again? (y/n)");
//		prompt.Execute();
//		while (prompt.isYes() == -1) {
//			prompt = opPrompt(pControl, "Bad Input: try again");
//			prompt.Execute();
//		}
//		if (!prompt.isYes())
//			break;
//		prompt = opPrompt(pControl, "Enter another file");
//		prompt.Execute();
//		path = prompt.response();
//	}
//
//	ifstream file;
//	file.open(path);
//
//	string data;
//	string drawColor;
//	string fillColor;
//	int isFilled;
//	int drawWidth;
//	int shapeCount;
//	file >> drawColor >> fillColor >> isFilled >> drawWidth >> shapeCount;
//	pUI->setDrawColor(drawColor);
//	pUI->setFillColor(fillColor, isFilled);
//	pUI->setPenWidth(drawWidth);
//	getline(file, data);
//	graph->Clear();
//	while (getline(file, data))
//		graph->Addshape(GUI::ParseShape(data));
//	file.close();
//
//	pUI->PrintMessage("Graph Loaded!");
//
//	return false;
//}
