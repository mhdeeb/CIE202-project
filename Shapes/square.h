#pragma once

#include "Rect.h"

class Square : public Rect
{
public:
	Square(Point, Point, GfxInfo);
	virtual ~Square();
	virtual void Draw(GUI*) const;
};
