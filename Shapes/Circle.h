#pragma once

#include "Shape.h"

class Circle : public shape
{
private:
	Point origin;
	double radius;
public:
	Circle(Point origin = {}, double radius = 0, GfxInfo shapeGfxInfo = {});
	Point getOrigin() const;
	double getRadius() const;
	void setRadius(double);
	void setOrigin(const Point&);
	virtual ~Circle() override;
	virtual void Draw(GUI*) const override;
	virtual string Serialize() const override;
	virtual bool isSelected(Point) const override;
};
