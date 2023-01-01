#include "Line.h"

#include <sstream>

Line::Line(Point P1, Point P2, const GfxInfo& shapeGfxInfo) : shape(shapeGfxInfo), Point1(P1), Point2(P2) {}
Point Line::getPoint1() const
{
	return Point1;
}
Point Line::getPoint2() const
{
	return Point2;
}
void Line::setPoint1(const Point& p1)
{
	Point1 = p1;
}
void Line::setPoint2(const Point& p2)
{
	Point2 = p2;
}
Line::~Line() = default;

void Line::Draw(GUI* pUI) const {
	pUI->DrawLine(this);
}

string Line::PrintInfo() const {
	string color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	return format("type: {: <20} fill: {: <20} draw: {: <20} {} {}", ShapesArray[RECTANGLE], color, gfxInfo.DrawClr.hex(), Point1.toString("p1"), Point2.toString("p2"));
}

string Line::Serialize() const {
	stringstream ss;
	ss << ShapesArray[LINE] << ' ' << id << ' ' << Point1.x << ' ' << Point1.y << ' ' << Point2.x << ' ' << Point2.y << ' ' << gfxInfo.DrawClr.hex() << ' ' << gfxInfo.isFilled << ' ' << gfxInfo.FillClr.hex() << ' ' << gfxInfo.BorderWdth;
	return ss.str();
}

bool Line::isSelected(Point p) const {
	if (Point1.x == Point2.x) {
		if (p.y >= min(Point1.y, Point2.y) && p.y <= max(Point1.y, Point2.y) && p.x == Point2.x)
			return true;
		return false;
	}
	double slope = double(Point2.y - Point1.y) / (Point2.x - Point1.x);
	if (double yIntercept = Point1.y - slope * Point1.x; p.x <= max(Point1.x, Point2.x) && p.x >= min(Point1.x, Point2.x) && p.y >= min(Point1.y, Point2.y) && p.y <= max(Point1.y, Point2.y)
		&& abs(p.y - (slope * p.x + yIntercept)) < 10)
		return true;
	return false;
}

Line* Line::Load(const string& data)
{
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	int borderWidth;
	string draw;
	string fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	auto* shape = new Line({ p1x, p1y }, { p2x, p2y }, gfx);
	shape->setID(id);
	return shape;
}

void Line::Transform(transformation func, double factor, Point origin)
{
	func(Point1, factor, origin);
	func(Point2, factor, origin);
}

Point Line::GetCenter() const
{
	return (Point1 + Point2) / 2;
}
