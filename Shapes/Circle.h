#pragma once

#include "Shape.h"

class Circle : public shape
{
private:
	Point origin;
	double radius;
public:
	Circle(Point, double, GfxInfo);
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};

