#pragma once

#include "Shape.h"

class Rect : public shape
{
protected:
	Point p1, p2;
public:
	Rect(Point, Point, GfxInfo);
	Rect() : p1{}, p2{} {}
	Point getC1() const;
	Point getC2() const;
	void setC1(Point);
	void setC2(Point);
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual bool isSelected(Point);
};
