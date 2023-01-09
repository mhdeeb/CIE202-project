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