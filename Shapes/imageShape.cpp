#include "imageShape.h"
#include <sstream>

imageShape::imageShape(Point p1, Point p2, const string& path): Rect(p1, p2), Image(new image(path)) {
	p1.x = min(p1.x, p2.x);
	p1.y = min(p1.y, p2.y);
	p2.x = max(p1.x, p2.x);
	p2.y = max(p1.y, p2.y);
	gfxInfo.BorderWdth = 3;
}

imageShape::~imageShape() {
	delete Image;
}

string imageShape::getPath() const {
	return Image->getPath();
}

void imageShape::Draw(GUI* pUI) const {
	Rect::Draw(pUI);
	if (Image)
		pUI->DrawImage(Image, p1.x + 3, p1.y + 3, p2.x - p1.x - 6, p2.y - p1.y - 6);
}

string imageShape::PrintInfo() const {
	return format("type: IMAGE path: {} {} {}", Image->getPath(), p1.toString("p1"), p2.toString("p2"));
}

string imageShape::Serialize() const {
	stringstream ss;
	ss << ShapesArray[IMAGE] << ' ' << id << ' ' << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << ' ' << getPath();
	return ss.str();
}

imageShape* imageShape::Load(const string& data) {
	stringstream ss(data);
	int id;
	int p1x;
	int p1y;
	int p2x;
	int p2y;
	string path;
	ss >> id >> p1x >> p1y >> p2x >> p2y >> path;
	auto* shape = new imageShape({p1x, p1y}, {p2x, p2y}, path);
	shape->setID(id);
	return shape;
}