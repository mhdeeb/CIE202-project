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

void shape::setID(int ID) {
	id = ID;
}