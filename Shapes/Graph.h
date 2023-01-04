#pragma once

#include "../GUI/GUI.h"
#include "Shape.h"

#include<filesystem>

//A class that is responsible on everything related to shapes
class Graph {
private:
	vector <shape*> shapesList; //a container to hold all shapes
	shape* selectedShape = nullptr;	//pointer to the currently selected shape
	string Clipboard;		//string to hold the copied shape
public:
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void deleteSelectedShape();   // delete a shpe from the shape List
	void Draw(GUI*) const;			//Draw the graph (draw all shapes)
	void Refresh(GUI*) const;
	shape* Getshape(Point p); //Search for a shape given a point inside the shape
	void setSelectedShape(shape*);
	shape* getSelectedShape() const;
	void Clear();
	void Copy();
	shape* Paste();
	vector<shape*> GetShapeList() const;
	void Load(filesystem::path name, GUI* pUI);
};
