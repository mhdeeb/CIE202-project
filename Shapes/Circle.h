#pragma once

#include "Shape.h"

class Circle : public shape
{
private:
	Point origin;
	double radius;
public:
	Circle(Point origin = {}, double radius = 0, GfxInfo shapeGfxInfo = {});
	Point getOrigin() const;
	double getRadius() const;
	void setRadius(double);
	void setOrigin(const Point&);
	~Circle() override;
	void Draw(GUI*) const override;
	string PrintInfo() const override;
	string Serialize() const override;
	bool isSelected(Point) const override;
	static Circle* Load(string data);
	void Transform(transformation func, double factor, Point origin) override;
	Point GetCenter() const override;
};
