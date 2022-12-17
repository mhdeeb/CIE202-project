#include "Square.h"
#include<math.h>

Square::Square(Point p1, Point p2, GfxInfo shapeGfxInfo) : shape( shapeGfxInfo)
{
	this->p1 = p1;
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	this-> p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	this-> p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}
Point Square::getC1() const
{
	return p1;
}

Point Square::getC2() const
{
	return p2;
}

void Square::setC1(const Point& p1)
{
	this->p1 = p1;
}
void Square::setC2(const Point& p2)
{
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	this-> p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	this-> p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

Square::~Square()
{}

void Square::Draw(GUI* pUI) const
{
	pUI->DrawSquare(this);
}

void Square::PrintInfo(GUI* pUI) const {
	pUI->PrintMessage("");
}


bool Square::isSelected(Point p) const {
	if (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x) && p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y))
		return true;
	return false;
}
