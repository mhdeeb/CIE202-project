#pragma once

#include "Shape.h"

class Line : public shape
{
private:
	Point Point1;
	Point Point2;
public:
	Line(Point, Point, GfxInfo shapeGfxInfo);
	Point getPoint1() const;
	Point getPoint2() const;
	void setPoint1(const Point &);
	void setPoint2(const Point&);
	virtual ~Line();
	virtual void Draw(GUI* pUI) const;
	virtual bool isSelected(Point);
};