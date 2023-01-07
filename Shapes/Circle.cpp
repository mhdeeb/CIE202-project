#include "Circle.h"

#include <sstream>

Circle::Circle(Point origin, double radius, const GfxInfo& shapeGfxInfo): shape(shapeGfxInfo), origin(origin), radius(radius), radiusp(origin + Point(int(radius), 0)) {}

Point Circle::getOrigin() const {
	return origin;
}

double Circle::getRadius() const {
	return radius;
}

void Circle::setRadius(double radius) {
	radiusp = origin + Point(int(radius), 0);
	this->radius = radius;
}

void Circle::setOrigin(const Point& origin) {
	radiusp = origin + Point(int(radius), 0);
	this->origin = origin;
}

Circle::~Circle() = default;

void Circle::Draw(GUI* pUI) const {
	pUI->DrawCircle(this);
}

string Circle::PrintInfo() const {
	string color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	return format("type: {: <20} fill: {: <20} draw: {: <20} {} radius: {:3.3f}", type(), color, gfxInfo.DrawClr.hex(), origin.toString("center"), radius);
}

string Circle::Serialize() const {
	stringstream ss;
	ss << type() << ' ' << id << ' ' << origin.x << ' ' << origin.y << ' ' << radius << ' ' << gfxInfo.DrawClr.hex() << ' ' << gfxInfo.isFilled << ' ' << gfxInfo.FillClr.hex() << ' ' << gfxInfo.BorderWdth;
	return ss.str();
}

bool Circle::isSelected(Point p) const {
	if (isHidden() && GetCenter() - 51 <= p && p <= GetCenter() + 51)
		return true;
	else if (p.distance(origin) <= radius)
		return true;
	return false;
}

Circle* Circle::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int borderWidth;
	string draw;
	string fill;
	bool isFilled;
	double radius;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> radius >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	auto* shape = new Circle({p1x, p1y}, radius, gfx);
	shape->setID(id);
	return shape;
}

void Circle::Transform(transformation func, double factor, Point origin) {
	func(this->origin, factor, origin);
	func(this->radiusp, factor, origin);
	radius = radiusp.distance(this->origin);
}

Point Circle::GetCenter() const {
	return origin;
}

pair<Point, Point> Circle::getBoundingBox() const {
	return {origin - Point(int(radius), int(radius)), origin + Point(int(radius), int(radius))};
}

string Circle::type() const {
	return "CIRCLE";
}