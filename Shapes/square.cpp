#include "Square.h"
#include<math.h>

Square::Square(Point p1, Point p2, GfxInfo shapeGfxInfo) : Rect(p1, p2, shapeGfxInfo)
{
	type = SQUARE;
	this->p1 = p1;
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	this-> p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	this-> p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

Square::~Square()
{}
