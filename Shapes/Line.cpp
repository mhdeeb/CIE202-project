#include "Line.h"

Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo), Point1(P1), Point2(P2) {}
Point Line::getPoint1() const
{
	return Point1;
}
Point Line::getPoint2() const
{
	return Point2;
}
void Line::setPoint1(const Point &p1)
{
	Point1 = p1;
}
void Line::setPoint2(const Point& p2)
{
	Point2 = p2;
}
Line::~Line() {}

void Line::Draw(GUI* pUI) const {	
	pUI->DrawLine(this);
}
