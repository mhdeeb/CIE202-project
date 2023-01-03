#pragma once

#include "../GUI/GUI.h"
#include <functional>

using transformation = const std::function<void(Point&, double parameter, const Point& origin)>&;
//Base class for all shapes
class shape {
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
	virtual void Transform(transformation, double, Point) = 0;
	virtual Point GetCenter() const = 0;
};
