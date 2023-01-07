#include "Rect.h"

#include <sstream>

Rect::Rect(Point p1, Point p2, const GfxInfo& shapeGfxInfo, int rx, int ry):shape(shapeGfxInfo), p1(p1), p2(p2), rx(rx), ry(ry) {}

Point Rect::getC1() const {
	return p1;
}

Point Rect::getC2() const {
	return p2;
}

void Rect::setC1(Point p1) {
	this->p1 = p1;
}

void Rect::setC2(Point p2) {
	this->p2 = p2;
}

void Rect::Draw(GUI* pUI) const {
	pUI->DrawRect(this, rx, ry);
}

string Rect::Serialize() const {
	stringstream ss;
	ss << type() << ' ' << id << ' ' << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << ' ' << gfxInfo.DrawClr.hex() << ' ' << gfxInfo.isFilled << ' ' << gfxInfo.FillClr.hex() << ' ' << gfxInfo.BorderWdth;
	return ss.str();
}

string Rect::PrintInfo() const {
	string color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	return format("type: {: <20} fill: {: <20} draw: {: <20} {} {}", type(), color, gfxInfo.DrawClr.hex(), p1.toString("p1"), p2.toString("p2"));
}

bool Rect::isSelected(Point p) const {
	if (isHidden() && GetCenter() - 51 <= p && p <= GetCenter() + 51)
		return true;
	if (p.x <= max(p1.x, p2.x) && p.x >= min(p1.x, p2.x) && p.y >= min(p1.y, p2.y) && p.y <= max(p1.y, p2.y))
		return true;
	return false;
}

Rect* Rect::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	int borderWidth;
	string draw, fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	Rect* shape = new Rect({p1x, p1y}, {p2x, p2y}, gfx);
	shape->setID(id);
	return shape;
}

void Rect::Transform(transformation func, double factor, Point origin) {
	func(p1, factor, origin);
	func(p2, factor, origin);
}

Point Rect::GetCenter() const {
	return (p1 + p2) / 2;
}

pair<Point, Point> Rect::getBoundingBox() const {
	return {p1, p2};
}

string Rect::type() const {
	return "RECTANGLE";
}