#include "Square.h"

#include <sstream>

Square::Square(Point p1, Point p2, const GfxInfo& shapeGfxInfo): Rect(p1, p2, shapeGfxInfo) {
	this->p1 = p1;
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	this->p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	this->p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

void Square::setC2(Point p2) {
	double L = sqrt((pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) / 2);
	this->p2.x = int(p1.x + ((p1.x < p2.x) ? L : -L));
	this->p2.y = int(p1.y + ((p1.y < p2.y) ? L : -L));
}

Square* Square::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	int borderWidth;
	string draw;
	string fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	Square* shape = new Square({p1x, p1y}, {p2x, p2y}, gfx);
	shape->setID(id);
	return shape;
}

string Square::type() const {
	return "SQUARE";
}