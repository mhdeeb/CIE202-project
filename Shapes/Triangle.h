#pragma once

#include "IrregPoly.h"

class Triangle: public IrregPoly {
public:
	explicit Triangle(const GfxInfo& shapeGfxInfo);
	~Triangle() override = default;
	void Draw(GUI* pUI) const override;
	static Triangle* Load(const string& data);
	string type() const override;
};
