#include "square.h"
#include"math.h"

square::square(Point P1, Point P2 , GfxInfo shapeGfxInfo) :shape(shapeGfxInfo)
{
	Corner1 = P1;
	Corner2.x = P1.x+ pow(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2), 0.5);
	Corner2.y = P1.y+ pow(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2), 0.5);
}

square::~square()
{}

void square::Draw(GUI* pUI) const
{
	//Call Output::DrawSqua to draw a square on the screen	
	pUI->DrawRect(Corner1, Corner2, ShpGfxInfo);
}