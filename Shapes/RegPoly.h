#pragma once
#include "IrregPoly.h"
#include "../GUI/GUI.h"
class RegPoly : public IrregPoly
{
private:
	Point c;
	double r;
	int v;
public:
	RegPoly(Point center, int vertices, GfxInfo shapeGfxInfo, double radius = 10);
	void update(Point center, double radius);
	virtual ~RegPoly() override;
	virtual void Draw(GUI*) const override;
	virtual void PrintInfo(GUI* pUI) const override;
};
