#include "Line.h"

Line::Line(Point P1, Point P2, GfxInfo shapeGfxInfo) : shape(shapeGfxInfo)
{
	Point1 = P1;
	Point2 = P2;

}
Line::~Line() {}

void Line::Draw(GUI* pUI) const {
	//Call Output::DrawRect to draw a rectangle on the screen	
	pUI->DrawLine(Point1, Point2, ShpGfxInfo);
}