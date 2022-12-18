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
	void setID(int id);
public:
	//Shape constructor
	shape(GfxInfo gfxInfo = {});
	//Shape destructor
	virtual ~shape() {}
	//Set shape selection
	void SetSelected(bool);
	//Return true if shape is selected 
	bool IsSelected() const;
	virtual bool isSelected(Point) const = 0;
	//absrtact function of Drawing the shape
	virtual void Draw(GUI* pUI) const = 0;
	//Get shape graphics info
	GfxInfo getGfxInfo() const;
	//Change draw color
	void setDrawColor(color);
	//Change fill color
	void setFillColor(color, bool);
	void setGfx(GfxInfo gfxInfo);
	virtual string Serialize() const = 0;
	virtual string PrintInfo() const = 0;

	////Rotate the shape
	//virtual void Rotate() = 0;
	////Resize the shape
	//virtual void Resize() = 0;
	////Move the shape
	//virtual void Move() = 0;
};
