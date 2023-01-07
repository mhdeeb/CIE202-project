#include "Triangle.h"

#include <sstream>

Triangle::Triangle(const GfxInfo& shapeGfxInfo): IrregPoly(shapeGfxInfo) {}

void Triangle::Draw(GUI* pUI) const {
	pUI->DrawIrregPoly(this);
}

Triangle* Triangle::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	int p3x;
	int p3y;
	int borderWidth;
	string draw;
	string fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> p3x >> p3y >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	Triangle* shape = new Triangle(gfx);
	shape->addPoint({p1x, p1y});
	shape->addPoint({p2x, p2y});
	shape->addPoint({p3x, p3y});
	shape->setID(id);
	return shape;
}

string Triangle::type() const {
	return "TRIANGLE";
}