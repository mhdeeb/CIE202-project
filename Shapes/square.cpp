#include "square.h"

square::square(Point P1, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2.x = 2 * p1.x;
	corner2.y = 2 * p1.y;
}

square::~square()
{}

void square::Draw(GUI* pUI) const
{
	//Call Output::DrawSqua to draw a square on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}