#pragma once

#include "Shape.h"

class IrregPoly : public shape
{
private:
	vector<int> xpoints, ypoints;
public:
	IrregPoly(GfxInfo);
	const int* getXpoints() const;
	const int* getYpoints() const;
	void addPoint(const Point&);
	void removePoint(int index);
	Point getPoint(int index);
	void setPoint(Point p, int index);
	int getSize() const;
	virtual ~IrregPoly();
	virtual void Draw(GUI*) const;
	virtual bool isSelected(Point);
};