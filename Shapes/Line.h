#pragma once

#include "Shape.h"

class Line : public shape
{
private:
	Point Point1;
	Point Point2;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
};
