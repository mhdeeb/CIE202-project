#include "RegPoly.h"

#include <numbers>
#include <sstream>

RegPoly::RegPoly(Point center, int vertices, GfxInfo shapeGfxInfo, double radius) : IrregPoly(shapeGfxInfo), r(radius), c(center), v(vertices) {
	type = REGULAR_POLYGON;
	for (double theta = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v)
		addPoint({ int(r * cos(theta) + c.x), int(r * sin(theta) + c.y) });
}

void RegPoly::update(Point center, double radius) {
	c = center;
	r = radius;
	for (double theta = 0, i = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v, ++i)
		setPoint({ int(r * cos(theta) + c.x), int(r * sin(theta) + c.y) }, i);
}

RegPoly::~RegPoly() {
	IrregPoly::~IrregPoly();
}

void RegPoly::Draw(GUI* pUI) const {
	pUI->DrawRegPoly(this);
}

RegPoly* RegPoly::Load(string data)
{
	stringstream ss(data);
	int id, p1x, p1y, vertices, borderWidth;
	double radius;
	string draw, fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> vertices >> radius >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	RegPoly* shape = new RegPoly({ p1x, p1y }, vertices, gfx, radius);
	shape->setID(id);
	return shape;
}
