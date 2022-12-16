#include "Graph.h"
#include<ranges>
#include<vector>

Graph::Graph()
{
	selectedShape = nullptr;
}

Graph::~Graph()
{
}

//==================================================================================//
//						shapes Management Functions								//
//==================================================================================//

//Add a shape to the list of shapes
void Graph::Addshape(shape* pShp)
{
	//Add a new shape to the shapes vector
	shapesList.push_back(pShp);
}
////////////////////////////////////////////////////////////////////////////////////
//Draw all shapes on the user interface
void Graph::Draw(GUI* pUI) const
{
	for (auto shapePointer : shapesList)
		shapePointer->Draw(pUI);
}

void Graph::Refresh(GUI* pUI) const
{
	pUI->Clear();
	Draw(pUI);
	pUI->CreateDrawToolBar();
	pUI->CreateStatusBar();
}

vector <shape* > Graph::GetShapeList() const {
	return  shapesList;
}
shape* Graph::Getshape(Point p)
{
	for (auto i : views::reverse(shapesList)) {
		if (i->isSelected(p)) {
			selectedShape = i;
			return selectedShape;
		}
	}	
	return nullptr;
}
void Graph::setSelectedShape(shape* pSsh) {
	selectedShape = pSsh;
}
