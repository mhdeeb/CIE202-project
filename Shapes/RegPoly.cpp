#include "RegPoly.h"
#include <numbers>

RegPoly::RegPoly(Point center, int vertices, GfxInfo shapeGfxInfo, double radius) : IrregPoly(shapeGfxInfo), r(radius), c(center), v(vertices) {
	for (double theta = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v) {
		xpoints.push_back(int(r * cos(theta) + c.x));
		ypoints.push_back(int(r * sin(theta) + c.y));
	}
}

void RegPoly::update(Point center, double radius) {
	c = center;
	r = radius;
	for (double theta = 0, i = 0; theta < 2 * numbers::pi; theta += 2 * numbers::pi / v, ++i) {
		xpoints[i] = int(r * cos(theta) + c.x);
		ypoints[i] = int(r * sin(theta) + c.y);
	}
}

RegPoly::~RegPoly() {
	IrregPoly::~IrregPoly();
}

void RegPoly::Draw(GUI* pUI) const {
	pUI->DrawRegPoly(this);
}
