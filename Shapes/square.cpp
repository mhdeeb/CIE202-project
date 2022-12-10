#include "Square.h"

Square::Square(Point P1, Point P2, GfxInfo shapeGfxInfo) : Rect(P1, P2, shapeGfxInfo)
{
	double L = sqrt((pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)) / 2);
	Corner2.x = P1.x + ((P1.x < P2.x) ? L : -L);
	Corner2.y = P1.y + ((P1.y < P2.y) ? L : -L);
}

Square::~Square()
{}

void Square::Draw(GUI* pUI) const
{
	//Call Output::DrawRect to draw a square on the screen	
	pUI->DrawRect(this);
}
bool Square::isSelected(Point p) {
	if (p.x <= max(Corner1.x, Corner2.x) && p.x >= min(Corner1.x, Corner2.x) && p.y >= min(Corner1.y, Corner2.y) && p.y <= max(Corner1.y, Corner2.y))
		return true;
	return false;
}
