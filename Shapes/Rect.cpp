#include "Rect.h"
#include "../DEFS.h"
#include <format>
using namespace std;

Rect::Rect(Point p1, Point p2, GfxInfo shapeGfxInfo) :shape(shapeGfxInfo), p1(p1), p2(p2) {}

Point Rect::getC1() const
{
	return p1;
}

Point Rect::getC2() const
{
	return p2;
}

void Rect::setC1(Point p1)
{
	this->p1 = p1;
}

void Rect::setC2(Point p2)
{
	this->p2 = p2;
}

Rect::~Rect() {}

void Rect::Draw(GUI* pUI) const {	
	pUI->DrawRect(this);
}

void Rect::PrintInfo(GUI* pUI) const {

	pUI->PrintMessage(format("type: {}  Filled?: {}  Fill Col:{}  Draw clr: {}\n Point1: ({},{}) Point2: ({},{})", ShapesArray[RECTANGLE], gfxInfo.isFilled, gfxInfo.FillClr.hex(), gfxInfo.DrawClr.hex(), p1.x, p1.y, p2.x, p2.y));
}

bool Rect::isSelected(Point p) const {
	if (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x) && p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y))
		return true;
	return false;
}

