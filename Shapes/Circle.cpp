#include "Circle.h"

Circle::Circle(Point origin, double radius, GfxInfo shapeGfxInfo) : origin(origin), radius(radius), shape(shapeGfxInfo) {}

Point Circle::getOrigin() const
{
	return origin;
}

double Circle::getRadius() const
{
	return radius;
}

Circle::~Circle() {}

void Circle::Draw(GUI* pUI) const {
	//Call Output::DrawCircle to draw a circle on the screen	
	pUI->DrawCircle(this);
}
bool Circle::isSelected(Point) {
	return false;
}
