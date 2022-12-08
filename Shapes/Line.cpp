#include "Line.h"

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
