#pragma once

#include"Shapes/Shape.h"

class Circle : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Circle(Point, Point, GfxInfo shapeGfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};

