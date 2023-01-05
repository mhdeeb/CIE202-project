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
void Graph::Addshape(shape* pShp) {
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);
}

void Graph::Removeshape(shape* pShp) {
	//Remove a shape from the shapes vector
	shapesList.erase(std::ranges::find(shapesList.begin(), shapesList.end(), pShp));
	delete pShp;
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
	if (pUI->getInterfaceMode())
		pUI->CreatePlayToolBar();
	else
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

vector<shape*> Graph::Paste() {
	vector<shape*> pastedShapes;
	stringstream ss(Clipboard);
	string line;
	while (getline(ss, line)) {
		shape* pShp = GUI::ParseShape(line);
		if (pShp != nullptr) {
			pastedShapes.push_back(pShp);
			Addshape(pShp);
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
	file >> drawColor >> fillColor >> isFilled >> drawWidth >> shapeCount;
	pUI->setDrawColor(drawColor);
	pUI->setFillColor(fillColor, isFilled);
	pUI->setPenWidth(drawWidth);
	getline(file, data);
	Clear();
	while (getline(file, data))
		Addshape(GUI::ParseShape(data));
	file.close();
	Refresh(pUI);
}