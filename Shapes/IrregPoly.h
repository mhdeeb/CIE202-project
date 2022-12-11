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
	Point getPoint(int index);
	int getSize() const;
	virtual ~IrregPoly();
	virtual void Draw(GUI*) const;
	virtual bool isSelected(Point);
};
