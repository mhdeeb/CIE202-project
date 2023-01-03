#include "Graph.h"
#include<ranges>
#include<vector>
using namespace std;

Graph::Graph() {
	selectedShape = nullptr;
}

Graph::~Graph() {}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp) {
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);
}

void Graph::deleteSelectedShape() {
	for (size_t i = 0; i < shapesList.size(); i++) {
		if (selectedShape == shapesList[i]) {
			delete selectedShape;
			selectedShape = nullptr;
			//delete a shape from the shapes vector
			shapesList.erase(shapesList.cbegin() + i);
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const {
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
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
shape* Graph::Getshape(Point p) {
	for (auto i : views::reverse(shapesList)) {
		if (i->isSelected(p)) {
			setSelectedShape(i);
			return selectedShape;
		}
	}
	setSelectedShape(nullptr);
	return selectedShape;
}
void Graph::setSelectedShape(shape* pSsh) {
	selectedShape = pSsh;
}
shape* Graph::getSelectedShape() const {
	return selectedShape;
}

void Graph::Clear() {
	while (!shapesList.empty()) {
		delete shapesList.back();
		shapesList.pop_back();
	}
}