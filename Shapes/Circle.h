#pragma once

#include "Shape.h"

class Circle : public shape
{
private:
	Point origin;
	double radius;
public:
	Circle(Point, double, GfxInfo);
	Point getOrigin() const;
	double getRadius() const;
	virtual ~Circle();
	virtual void Draw(GUI* pUI) const;
};
