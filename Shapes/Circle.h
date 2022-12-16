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
	virtual ~Circle() override;
	virtual void Draw(GUI*) const override;
	virtual bool isSelected(Point) const override;
};
