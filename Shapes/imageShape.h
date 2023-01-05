#pragma once
#include "Rect.h"
class imageShape: public Rect {
private:
	image* Image;
public:
	imageShape(Point p1, Point p2, const string& path);
	~imageShape() override;
	string getPath() const;
	void Draw(GUI* pUI) const override;
	string PrintInfo() const override;
	string Serialize() const override;
	static imageShape* Load(const string& data);
};