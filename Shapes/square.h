#pragma once

#include "Rect.h"

class Square: public Rect {
public:
	Square(Point p1, Point p2, const GfxInfo& shapeGfxInfo);
	~Square() override = default;
	void setC2(Point p2);
	static Square* Load(const string& data);
	string type() const override;
};
