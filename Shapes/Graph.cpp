#include "Graph.h"
#include<ranges>
#include<vector>
#include<fstream>
#include "Circle.h"
using namespace std;

Graph::Graph() {}

Graph::~Graph() {}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp, GUI* pUI) {
	shapesList.push_back(pShp);
	updateHistory(pUI);
}

void Graph::Removeshape(shape* pShp, GUI* pUI) {
	shapesList.erase(std::ranges::find(shapesList.begin(), shapesList.end(), pShp));
	delete pShp;
	updateHistory(pUI);
}

////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const {
	for (shape const* shapePointer : shapesList) {
		shapePointer->Draw(pUI);
		if (GroupPreview && shapePointer->getId() != -1)
			Circle(shapePointer->GetCenter(), 5, {ColorsArray[shapePointer->getId()], ColorsArray[shapePointer->getId()], true}).Draw(pUI);
	}
}

void Graph::Refresh(GUI* pUI) const {
	pUI->Clear();
	Draw(pUI);
	if (pUI->getInterfaceMode()) {
		pUI->CreatePlayToolBar();
	} else
		pUI->CreateDrawToolBar();
	pUI->CreateStatusBar();
}

vector <shape* > Graph::GetShapeList() const {
	return  shapesList;
}

bool Graph::getGroupPreview() const {
	return GroupPreview;
}

void Graph::setGroupPreview(bool b) {
	GroupPreview = b;
}

void Graph::undo(GUI* pUI) {
	if (historyIndex > 0) {
		historyIndex--;
		LoadStr(history[historyIndex], pUI);
	}
}

void Graph::redo(GUI* pUI) {
	if (historyIndex < history.size() - 1) {
		historyIndex++;
		LoadStr(history[historyIndex], pUI);
	}
}

void Graph::Hide(GUI* pUI) const {
	for (auto shape : GetShapeList())
		shape->Hide();
	Refresh(pUI);
}

void Graph::Show(GUI* pUI) const {
	for (auto shape : GetShapeList())
		shape->Show();
	Refresh(pUI);
}

void Graph::updateHistory(const GUI* pUI) {
	if (historyIndex == -1)
		return;
	stringstream ss;
	ss << pUI->getCrntDrawColor().hex() << ' ' << pUI->getCrntFillColor().hex() << ' ' << pUI->getIsfilled() << ' ' << pUI->getCrntPenWidth() << endl << GetShapeList().size() << endl;

	for (const shape* shape : GetShapeList())
		ss << shape->Serialize() << endl;
	string data = ss.str();
	if (history.size() && data == history[historyIndex])
		return;
	if (historyIndex < history.size() - 1)
		history.erase(history.begin() + historyIndex, history.end());
	else
		historyIndex = history.size();
	history.push_back(data);
}

shape* Graph::Getshape(Point p) {
	for (auto i : views::reverse(shapesList))
		if (i->isSelected(p))
			return i;
	return nullptr;
}
vector<shape*> Graph::getSelectedShapes() const {
	vector <shape*> selectedShapes;
	for (auto i : shapesList)
		if (i->IsSelected())
			selectedShapes.push_back(i);
	return selectedShapes;
}

void Graph::updateSelectedShapes(GUI const* pUI) const {
	if (!getGroupPreview()) {
		for (auto shape : getSelectedShapes())
			shape->SetSelected(false);
	} else {
		for (auto shape : GetShapeList())
			if (shape->getId() == pUI->getGid())
				shape->SetSelected(true);
			else
				shape->SetSelected(false);
	}
}

void Graph::Clear() {
	while (!shapesList.empty()) {
		delete shapesList.back();
		shapesList.pop_back();
	}
}

void Graph::Copy() {
	stringstream ss;
	for (const shape* shape : getSelectedShapes())
		ss << shape->Serialize() << '\n';
	Clipboard = ss.str();
}

vector<shape*> Graph::Paste(GUI* pUI) {
	vector<shape*> pastedShapes;
	stringstream ss(Clipboard);
	string line;
	while (getline(ss, line)) {
		shape* pShp = GUI::ParseShape(line);
		if (pShp != nullptr) {
			pastedShapes.push_back(pShp);
			Addshape(pShp, pUI);
		}
	}
	return pastedShapes;
}

void Graph::Load(const filesystem::path& name, GUI* pUI) {
	ifstream file;
	file.open(name);
	string data;
	string drawColor;
	string fillColor;
	int isFilled;
	int drawWidth;
	int shapeCount;
	getline(file, data);
	stringstream ss(data);
	ss >> drawColor >> fillColor >> isFilled >> drawWidth;
	getline(file, data);
	stringstream(data) >> shapeCount;
	pUI->setDrawColor(drawColor);
	pUI->setFillColor(fillColor, isFilled);
	pUI->setPenWidth(drawWidth);
	Clear();
	while (getline(file, data))
		Addshape(GUI::ParseShape(data), pUI);
	file.close();
	Refresh(pUI);
}

void Graph::LoadStr(const string& data, GUI* pUI) {
	int histoIndex = historyIndex;
	historyIndex = -1;
	string line;
	string drawColor;
	string fillColor;
	int isFilled;
	int drawWidth;
	int shapeCount;
	stringstream ds(data);
	getline(ds, line);
	stringstream ls(line);
	ls >> drawColor >> fillColor >> isFilled >> drawWidth;
	getline(ds, line);
	stringstream(line) >> shapeCount;
	pUI->setDrawColor(drawColor);
	pUI->setFillColor(fillColor, isFilled);
	pUI->setPenWidth(drawWidth);
	Clear();
	while (getline(ds, line))
		Addshape(GUI::ParseShape(line), pUI);
	Refresh(pUI);
	historyIndex = histoIndex;
}