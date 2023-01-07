#include "RegPoly.h"

#include <numbers>
#include <sstream>

RegPoly::RegPoly(Point center, int vertices, const GfxInfo& shapeGfxInfo, double radius): IrregPoly(shapeGfxInfo), r(radius), c(center), v(vertices) {
	for (double theta = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v)
		addPoint({int(r * cos(theta) + c.x), int(r * sin(theta) + c.y)});
}

void RegPoly::update(Point center, double radius) {
	c = center;
	r = radius;
	int i = 0;
	for (double theta = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v, ++i)
		setPoint({int(r * cos(theta) + c.x), int(r * sin(theta) + c.y)}, i);
}

void RegPoly::Draw(GUI* pUI) const {
	pUI->DrawRegPoly(this);
}

RegPoly* RegPoly::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int vertices;
	int borderWidth;
	double radius;
	string draw;
	string fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> vertices >> radius >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	RegPoly* shape = new RegPoly({p1x, p1y}, vertices, gfx, radius);
	shape->setID(id);
	return shape;
}

string RegPoly::type() const {
	return "REGULAR_POLYGON";
}