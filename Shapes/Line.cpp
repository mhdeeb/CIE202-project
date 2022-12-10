#include "Line.h"
#include<iostream>
using namespace std;

Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	Point1 = P1;
	Point2 = P2;
}
Point Line::getPoint1() const
{
	return Point1;
}
Point Line::getPoint2() const
{
	return Point2;
}
Line::~Line() {}

void Line::Draw(GUI* pUI) const {
	//Call Output::DrawLine to draw a line on the screen	
	pUI->DrawLine(this);
}

bool Line::isSelected(Point p) {
	if (Point1.x == Point2.x) {
		if (p.y >= min(Point1.y, Point2.y) && p.y <= max(Point1.y, Point2.y) && p.x== Point2.x)
			return true;
	}
	if (p.x <= max(Point1.x, Point2.x) && p.x >= min(Point1.x, Point2.x) && p.y >= min(Point1.y, Point2.y) && p.y <= max(Point1.y, Point2.y) 
		&& (int(double(p.y-Point1.y)/(p.x - Point1.x))) == int(double(Point2.y - Point1.y)/(Point2.x - Point1.x)))
		return true;
	return false;
}
