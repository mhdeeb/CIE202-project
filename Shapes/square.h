#pragma once

#include "Rect.h"

class Square : public Rect
{
public:
	Square(Point, Point, GfxInfo);
	virtual ~Square() override;
	void setC2(Point p2);
};
