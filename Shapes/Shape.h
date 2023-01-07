#pragma once

#include "../GUI/GUI.h"
#include <functional>

using transformation = const std::function<void(Point& point, double parameter, const Point& origin)>&;
#define TRANSFORMATION Point& point, double parameter, const Point& origin

//Base class for all shapes
class shape {
protected:
	//Shape ID
	int id = -1;
	//Shape graphics info
	GfxInfo gfxInfo;
	void setID(int id);
	bool hidden = false;
public:
	virtual string type() const = 0;
	//Shape constructor
	explicit shape(const GfxInfo& gfxInfo = {});
	//Shape destructor
	virtual ~shape() = default;
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
	void setGfx(const GfxInfo& gfxInfo);
	virtual string Serialize() const = 0;
	virtual string PrintInfo() const = 0;
	virtual void Transform(transformation func, double factor, Point origin) = 0;
	virtual Point GetCenter() const = 0;
	int getId() const;
	void setId(int id);
	virtual pair<Point, Point> getBoundingBox() const = 0;
	void Hide();
	void Show();
	bool isHidden() const;
	virtual string signiture() const;
};
