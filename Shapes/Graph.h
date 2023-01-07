#pragma once

#include "../GUI/GUI.h"
#include "Shape.h"

#include <filesystem>

//A class that is responsible on everything related to shapes
class Graph {
private:
	vector <shape*> shapesList; //a container to hold all shapes
	string Clipboard;		//string to hold the copied shape
	vector<string> history;			//string to hold the history of the actions
	unsigned int historyIndex = 0;		//index of the history
	bool GroupPreview = false;
public:
	Graph();
	~Graph();
	void Addshape(shape* pFig, GUI* pUI); //Adds a new shape to the shapesList
	void Removeshape(shape* pShp, GUI* pUI); //Removes a shape from the shapesList
	void Draw(GUI*) const;			//Draw the graph (draw all shapes)
	void Refresh(GUI*) const;
	shape* Getshape(Point p); //Search for a shape given a point inside the shape
	vector<shape*> getSelectedShapes() const;
	void updateSelectedShapes(GUI const* pUI) const;
	void Clear();
	void Copy();
	vector<shape*> Paste(GUI* pUI);
	vector<shape*> GetShapeList() const;
	void Load(const filesystem::path& name, GUI* pUI);
	void LoadStr(const string& data, GUI* pUI);
	bool getGroupPreview() const;
	void setGroupPreview(bool b);
	void updateHistory(const GUI* pUI);
	void undo(GUI* pUI);
	void redo(GUI* pUI);
	void Hide(GUI* pUI) const;
	void Show(GUI* pUI) const;
	void limitSize();
};
