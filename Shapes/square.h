#pragma once

#include "Rect.h"

class Square : public Rect
{
public:
	Square(Point, Point, GfxInfo);
	void setC2(Point);
	virtual ~Square();
	virtual void Draw(GUI*) const;
	virtual bool isSelected(Point);
};
