#pragma once

#include "Shape.h"

class IrregPoly: public shape {
protected:
	vector<int> xpoints;
	vector<int> ypoints;
	Point center{0, 0};;
public:
	explicit IrregPoly(const GfxInfo& shapeGfxInfo);
	const int* getXpoints() const;
	const int* getYpoints() const;
	Point GetCenter() const override;
	void addPoint(const Point&);
	void removePoint(int index);
	Point getPoint(int index) const;
	void setPoint(Point p, int index);
	int getSize() const;
	~IrregPoly() override;
	void Draw(GUI*) const override;
	bool isSelected(Point) const override;
	string PrintInfo() const override;
	string Serialize() const override;
	static double Area(Point, Point, Point);
	void updateCenter();
	static IrregPoly* Load(const string& data);
	void Transform(transformation func, double factor, Point origin) override;
	pair<Point, Point> getBoundingBox() const override;
	string type() const override;
};
