#pragma once

#include "Shape.h"

class Rect: public shape {
protected:
	Point p1;
	Point p2;
	int rx;
	int ry;
public:
	Rect(Point p1 = {}, Point p2 = {}, const GfxInfo& shapeGfxInfo = {}, int rx = 0, int ry = 0);
	Point getC1() const;
	Point getC2() const;
	void setC1(Point);
	void setC2(Point);
	~Rect() override = default;
	void Draw(GUI* pUI) const override;
	string Serialize() const override;
	string PrintInfo() const override;
	bool isSelected(Point) const override;
	static Rect* Load(const string& data);
	void Transform(transformation func, double factor, Point origin) override;
	Point GetCenter() const override;
	pair<Point, Point> getBoundingBox() const override;
	string type() const override;
};
