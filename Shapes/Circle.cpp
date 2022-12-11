#include "Circle.h"

Circle::Circle(Point origin={}, double radius = 0, GfxInfo shapeGfxInfo = {}) : shape(shapeGfxInfo), origin(origin), radius(radius) {}

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
bool Circle::isSelected(Point) {
	return false;
}
