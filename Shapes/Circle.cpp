#include "Circle.h"
//#include <format>

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

string Circle::Serialize() const {
	string color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	return format("type: {: <20} fill: {: <20} draw: {: <20} {} radius: {:3.3f}", ShapesArray[CIRCLE], color, gfxInfo.DrawClr.hex(), origin.toString("center"), radius);
}

bool Circle::isSelected(Point p) const {
	if (p.distance(origin) <= radius)
		return true;
	return false;
}
