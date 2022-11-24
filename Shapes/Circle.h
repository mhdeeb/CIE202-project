#pragma once

#include "Shape.h"

class Circle : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	Circle(Point, double, GfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};

