#pragma once

#include "Rect.h"

class Square : public Rect
{
	Point p1, p2;

public:
	Square(Point, Point, GfxInfo);
	virtual ~Square() override;
};
