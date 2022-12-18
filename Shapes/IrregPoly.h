#pragma once

#include "Shape.h"

class IrregPoly : public shape
{
protected:
	vector<int> xpoints, ypoints;
	Point center;
	shapeName type;
public:
	IrregPoly(GfxInfo);
	const int* getXpoints() const;
	const int* getYpoints() const;
	Point getCenter() const;
	void addPoint(const Point&);
	void removePoint(int index);
	Point getPoint(int index) const;
	void setPoint(Point p, int index);
	int getSize() const;
	virtual ~IrregPoly() override;
	virtual void Draw(GUI*) const override;
	virtual bool isSelected(Point) const override;
	virtual string Serialize() const override;
	static double Area(Point, Point, Point);
	void updateCenter();
};
