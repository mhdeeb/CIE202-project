#pragma once

#include "Shape.h"

class Line: public shape {
private:
	Point Point1;
	Point Point2;
public:
	Line(Point, Point, const GfxInfo& shapeGfxInfo);
	Point getPoint1() const;
	Point getPoint2() const;
	void setPoint1(const Point&);
	void setPoint2(const Point&);
	~Line() override;
	void Draw(GUI* pUI) const override;
	string PrintInfo() const override;
	string Serialize() const override;
	bool isSelected(Point) const override;
	static Line* Load(const string& data);
	void Transform(transformation func, double factor, Point origin) override;
	Point GetCenter() const override;
};
