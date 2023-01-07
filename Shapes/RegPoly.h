#pragma once
#include "IrregPoly.h"
#include "../GUI/GUI.h"
class RegPoly: public IrregPoly {
private:
	double r;
	Point c;
	int v;
public:
	RegPoly(Point center, int vertices, const GfxInfo& shapeGfxInfo, double radius = 10);
	void update(Point center, double radius);
	~RegPoly() override = default;
	void Draw(GUI*) const override;
	static RegPoly* Load(const string& data);
	string type() const override;
};
