#include "Triangle.h"

#include <sstream>

Triangle::Triangle(GfxInfo shapeGfxInfo): IrregPoly(shapeGfxInfo)
{
	type = TRIANGLE;
}

Triangle::~Triangle() {}

void Triangle::Draw(GUI* pUI) const {	
	pUI->DrawIrregPoly(this);
}

Triangle* Triangle::Load(string data)
{
	stringstream ss(data);
	int id, p1x, p1y, p2x, p2y, p3x, p3y, borderWidth;
	string draw, fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> p3x >> p3y >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	Triangle* shape = new Triangle(gfx);
	shape->addPoint({ p1x, p1y });
	shape->addPoint({ p2x, p2y });
	shape->addPoint({ p3x, p3y });
	shape->setID(id);
	return shape;
}
