#include "Circle.h"

Circle::Circle(Point origin, double radius, GfxInfo shapeGfxInfo): origin(origin), radius(radius), shape(shapeGfxInfo) {}

Circle::~Circle() {}

void Circle::Draw(GUI* pUI) const {
	//Call Output::DrawCircle to draw a rectangle on the screen	
	pUI->DrawCircle(origin, radius, ShpGfxInfo);
}