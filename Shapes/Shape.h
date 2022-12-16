#pragma once

#include "../GUI/GUI.h"

//Base class for all shapes
class shape
{
private:
	static int shapeCount;
protected:
	//Shape ID
	int id;
	//Shape graphics info
	GfxInfo gfxInfo;
public:
	//Shape constructor
	shape(GfxInfo);
	//Shape default constructor
	shape() {}
	//Shape destructor
	virtual ~shape() {}
	//Set shape selection
	void SetSelected(bool);
	//Return true if shape is selected 
	bool IsSelected() const;
	virtual bool isSelected(Point) = 0;
	//absrtact function of Drawing the shape
	virtual void Draw(GUI* pUI) const = 0;
	//Get shape graphics info
	GfxInfo getGfxInfo() const;
	//Change draw color
	void setDrawColor(color);
	//Change fill color
	void setFillColor(color, bool);
	////Rotate the shape
	//virtual void Rotate() = 0;
	////Resize the shape
	//virtual void Resize() = 0;
	////Move the shape
	//virtual void Move() = 0;
	////Save the shape parameters to the file
	//virtual void Save(ofstream &OutFile) = 0;
	//Load the shape parameters to the file
	//virtual void Load(ifstream &Infile) = 0;
	////print all shape info on the status bar
	//virtual void PrintInfo(Output* pOut) = 0;
};
