#include "shape.h"

shape::shape(const GfxInfo& gfxInfo): gfxInfo(gfxInfo) {}

void shape::SetSelected(bool s) {
	gfxInfo.isSelected = s;
}

bool shape::IsSelected() const {
	return gfxInfo.isSelected;
}

GfxInfo shape::getGfxInfo() const {
	return gfxInfo;
}

void shape::setDrawColor(color drawColor) {
	gfxInfo.DrawClr = drawColor;
}

void shape::setFillColor(color fillColor, bool isFilled = true) {
	gfxInfo.isFilled = isFilled;
	gfxInfo.FillClr = fillColor;
}

void shape::setGfx(const GfxInfo& gfxInfo) {
	this->gfxInfo = gfxInfo;
}

int shape::getId() const {
	return id;
}

void shape::setId(int id) {
	this->id = id;
}

void shape::Hide() {
	auto [p1, p2] = getBoundingBox();
	Point s = p2 - p1;
	double scale = 100. / max(s.x, s.y);
	Transform([](TRANSFORMATION) {
		point.translate(-origin).scale(parameter).translate(origin);
		}, scale, GetCenter());
	hidden = true;
}

void shape::Show() {
	hidden = false;
}

bool shape::isHidden() const {
	return hidden;
}

string shape::signiture() const {
	shape* s = GUI::ParseShape(Serialize());
	s->setID(0);
	s->Transform([](TRANSFORMATION) {
		point.translate(origin);
		}, 0, -GetCenter());
	return s->Serialize();
}

void shape::setID(int ID) {
	id = ID;
}