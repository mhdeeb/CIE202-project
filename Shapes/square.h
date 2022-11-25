#pragma once
#include "Shape.h"

class square : public shape
{
private:
	Point Corner1;
	Point Corner2;
public:
	square(Point, GfxInfo shapeGfxInfo);
	virtual ~square();
	virtual void Draw(GUI* pUI) const;
};
