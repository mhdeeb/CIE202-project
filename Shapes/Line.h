#pragma once

#include "Shape.h"

class Line : public shape
{
private:
	Point Point1;
	Point Point2;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	Point getPoint1() const;
	Point getPoint2() const;
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
	virtual bool isSelected(Point);
};
