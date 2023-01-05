#pragma once

#include "../GUI/GUI.h"
#include "Shape.h"

#include <filesystem>

//A class that is responsible on everything related to shapes
class Graph {
private:
	vector <shape*> shapesList; //a container to hold all shapes
	string Clipboard;		//string to hold the copied shape
	bool GroupPreview = false;
public:
	Graph();
	~Graph();
	void Addshape(shape* pFig); //Adds a new shape to the shapesList
	void Removeshape(shape* pShp); //Removes a shape from the shapesList
	void Draw(GUI*) const;			//Draw the graph (draw all shapes)
	void Refresh(GUI*) const;
	shape* Getshape(Point p); //Search for a shape given a point inside the shape
	vector<shape*> getSelectedShapes() const;
	void Clear();
	void Copy();
	vector<shape*> Paste();
	vector<shape*> GetShapeList() const;
	void Load(const filesystem::path& name, GUI* pUI);
	bool getGroupPreview() const;
	void setGroupPreview(bool b);
};
