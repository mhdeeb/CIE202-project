#pragma once

#include "Shape.h"

class Rect : public shape
{
protected:
	Point p1;
	Point p2;
	shapeType type;
public:
	Rect(Point = {}, Point = {}, GfxInfo = {});
	Point getC1() const;
	Point getC2() const;
	void setC1(Point);
	void setC2(Point);
	~Rect() override;
	void Draw(GUI* pUI) const override;
	string Serialize() const override;
	string PrintInfo() const override;
	bool isSelected(Point) const override;
	static Rect* Load(string data);
	void Transform(transformation func, double factor, Point origin) override;
	Point GetCenter() const override;
};
