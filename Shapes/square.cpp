#include "square.h"
#include"math.h"

square::square(Point P1, Point P2 , GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	double L = sqrt((pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)) / 2);
	Corner2.x = P1.x + ((P1.x < P2.x) ? L : -L);
	Corner2.y = P1.y + ((P1.y < P2.y) ? L : -L);
}

square::~square()
{}

void square::Draw(GUI* pUI) const
{
	//Call Output::DrawSqua to draw a square on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}