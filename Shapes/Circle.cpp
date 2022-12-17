#include "Circle.h"

Circle::Circle(Point origin, double radius, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo), origin(origin), radius(radius) {}

Point Circle::getOrigin() const
{
	return origin;
}

double Circle::getRadius() const
{
	return radius;
}

void Circle::setRadius(double radius)
{
	this->radius = radius;
}

void Circle::setOrigin(const Point &origin)
{
	this->origin = origin;
}

Circle::~Circle() {}

void Circle::Draw(GUI* pUI) const {	
	pUI->DrawCircle(this);
}

void Circle::PrintInfo(GUI* pUI) const {
	pUI->PrintMessage("");
}


bool Circle::isSelected(Point p) const {
	if (p.distance(origin) <= radius)
		return true;
	return false;
}
