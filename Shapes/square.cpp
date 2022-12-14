#include "Square.h"

Square::Square(Point p1, Point p2, GfxInfo shapeGfxInfo) : Rect(p1, p2, shapeGfxInfo)
{
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	Rect::p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	Rect::p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

void Square::setC2(Point p2)
{
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	Rect::p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	Rect::p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

Square::~Square()
{}

void Square::Draw(GUI* pUI) const
{
	pUI->DrawRect(this);
}
bool Square::isSelected(Point p) {
	if (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x) && p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y))
		return true;
	return false;
}
