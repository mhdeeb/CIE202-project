#pragma once

#include "Shape.h"

class IrregPoly: public shape {
protected:
	vector<int> xpoints, ypoints;
	Point center;
	shapeType type;
public:
	IrregPoly(GfxInfo);
	const int* getXpoints() const;
	const int* getYpoints() const;
	Point GetCenter() const override;
	void addPoint(const Point&);
	void removePoint(int index);
	Point getPoint(int index) const;
	void setPoint(Point p, int index);
	int getSize() const;
	virtual ~IrregPoly() override;
	virtual void Draw(GUI*) const override;
	virtual bool isSelected(Point) const override;
	virtual string PrintInfo() const override;
	virtual string Serialize() const override;
	static double Area(Point, Point, Point);
	void updateCenter();
	static IrregPoly* Load(string data);
	void Transform(transformation func, double factor, Point origin) override;
	pair<Point, Point> getBoundingBox() const override;
};
