#include "Circle.h"

#include <sstream>

Circle::Circle(Point origin, double radius, GfxInfo shapeGfxInfo): shape(shapeGfxInfo), origin(origin), radius(radius), radiusp(origin + Point(radius, 0)) {}

Point Circle::getOrigin() const {
	return origin;
}

double Circle::getRadius() const {
	return radius;
}

void Circle::setRadius(double radius) {
	radiusp.x = int(radius) + origin.x;
	this->radius = radius;
}

void Circle::setOrigin(const Point& origin) {
	radiusp = origin + Point(radius, 0);
	this->origin = origin;
}

Circle::~Circle() {}

void Circle::Draw(GUI* pUI) const {
	pUI->DrawCircle(this);
}

string Circle::PrintInfo() const {
	string color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	return format("type: {: <20} fill: {: <20} draw: {: <20} {} radius: {:3.3f}", ShapesArray[CIRCLE], color, gfxInfo.DrawClr.hex(), origin.toString("center"), radius);
}

string Circle::Serialize() const {
	stringstream ss;
	ss << ShapesArray[CIRCLE] << ' ' << id << ' ' << origin.x << ' ' << origin.y << ' ' << radius << ' ' << gfxInfo.DrawClr.hex() << ' ' << gfxInfo.isFilled << ' ' << gfxInfo.FillClr.hex() << ' ' << gfxInfo.BorderWdth;
	return ss.str();
}

bool Circle::isSelected(Point p) const {
	if (p.distance(origin) <= radius)
		return true;
	return false;
}

Circle* Circle::Load(string data) {
	stringstream ss(data);
	int id, p1x, p1y, borderWidth;
	string draw, fill;
	bool isFilled;
	double radius;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> radius >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	Circle* shape = new Circle({p1x, p1y}, radius, gfx);
	shape->setID(id);
	return shape;
}

void Circle::Transform(transformation func, double factor, Point origin) {
	func(this->origin, factor, origin);
	func(this->radiusp, factor, origin);
	radius = radiusp.x - this->origin.x;
}

Point Circle::GetCenter() const {
	return origin;
}