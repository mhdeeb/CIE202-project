#pragma once

#include "Shape.h"

class Rect : public shape
{
protected:
	Point Corner1;
	Point Corner2;
public:
	Rect(Point, Point, GfxInfo);
	Rect(){}
	Point getC1() const;
	Point getC2() const;
	virtual ~Rect();
	virtual void Draw(GUI* pUI) const;
	virtual bool isSelected(Point);
};
