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
	void setRadius(double);
	void setOrigin(const Point&);
	virtual ~Circle();
	virtual void Draw(GUI*) const;
	virtual bool isSelected(Point);
};
