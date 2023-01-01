#include "IrregPoly.h"

#include <numeric>
#include <sstream>

IrregPoly::IrregPoly(GfxInfo shapeGfxInfo) : shape(shapeGfxInfo), type(IRREGULAR_POLYGON), center({ 0,0 }) {}

const int* IrregPoly::getXpoints() const
{
	return &xpoints[0];
}

const int* IrregPoly::getYpoints() const
{
	return &ypoints[0];
}

Point IrregPoly::GetCenter() const {
	return center;
}

void IrregPoly::addPoint(const Point& point)
{
	xpoints.push_back(point.x);
	ypoints.push_back(point.y);
	updateCenter();
}

void IrregPoly::removePoint(int index)
{
	if (index < 0)
		index = getSize() + index;
	xpoints.erase(xpoints.begin() + index);
	ypoints.erase(ypoints.begin() + index);
	updateCenter();
}

Point IrregPoly::getPoint(int index) const
{
	if (index < 0)
		index = getSize() + index;
	return { xpoints[index], ypoints[index] };
}

void IrregPoly::setPoint(Point p, int index)
{
	if (index < 0)
		index = getSize() + index;
	xpoints[index] = p.x;
	ypoints[index] = p.y;
	updateCenter();
}

int IrregPoly::getSize() const
{
	return xpoints.size();
}

IrregPoly::~IrregPoly() {
	xpoints.clear();
	ypoints.clear();
}

void IrregPoly::Draw(GUI* pUI) const {
	pUI->DrawIrregPoly(this);
}


string IrregPoly::PrintInfo() const {
	string color, data, points = "";
	color = (gfxInfo.isFilled) ? gfxInfo.FillClr.hex() : "null";
	data = format("type: {: <20} fill: {: <20} draw: {: <20}\n", ShapesArray[type], color, gfxInfo.DrawClr.hex());
	for (size_t i = 0; i < xpoints.size(); i++)
		points += getPoint(i).toString(format("p{}", i)) + "  ";
	return data + points;
}

string IrregPoly::Serialize() const {
	stringstream ss;
	ss << ShapesArray[IRREGULAR_POLYGON] << ' ' << id << ' ' << xpoints.size() << ' ';
	for (size_t i = 0; i < xpoints.size(); i++)
		ss << xpoints[i] << ' ' << ypoints[i] << ' ';
	ss << gfxInfo.DrawClr.hex() << ' ' << gfxInfo.isFilled << ' ' << gfxInfo.FillClr.hex() << ' ' << gfxInfo.BorderWdth;
	return ss.str();
}

double IrregPoly::Area(Point p1, Point p2, Point p3) {
	return abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
}

void IrregPoly::updateCenter() {
	center.x = accumulate(xpoints.cbegin(), xpoints.cend(), 0) / xpoints.size();
	center.y = accumulate(ypoints.cbegin(), ypoints.cend(), 0) / ypoints.size();
}

IrregPoly* IrregPoly::Load(string data)
{
	stringstream ss(data);
	int id, px, py, n, borderWidth;
	string draw, fill;
	bool isFilled;
	GfxInfo gfx;
	ss >> id >> n;
	IrregPoly* shape = new IrregPoly(gfx);
	for (int i = 0; i < n; i++)
	{
		ss >> px >> py;
		shape->addPoint({ px, py });
	}
	ss >> draw >> isFilled >> fill >> borderWidth;
	gfx.BorderWdth = borderWidth;
	gfx.DrawClr = draw;
	gfx.FillClr = fill;
	gfx.isFilled = isFilled;
	shape->setGfx(gfx);
	shape->setID(id);
	return shape;
}

bool IrregPoly::isSelected(Point p) const {
	double area = 0, testArea = 0;
	int nupberOfPoints = xpoints.size() - 1;
	for (int i = -1; i < nupberOfPoints; ++i)
	{
		area += Area(center, getPoint(i), getPoint(i + 1));
		testArea += Area(p, getPoint(i), getPoint(i + 1));
	}
	return area == testArea;
}

void IrregPoly::Transform(transformation func, double factor, Point origin)
{
	for (int i = 0; i < getSize(); ++i) {
		Point p = { xpoints[i], ypoints[i] };
		func(p, factor, origin);
		xpoints[i] = p.x;
		ypoints[i] = p.y;
	}
}
