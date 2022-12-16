#pragma once

#include "Shape.h"

class Square : public shape
{
	Point p1, p2;

public:
	Square(Point, Point, GfxInfo);
	Point getC1() const;
	Point getC2() const;
	void setC1(const Point&);
	void setC2(const Point&);
	virtual ~Square();
	virtual void Draw(GUI*) const;
	virtual bool isSelected(Point);
};
