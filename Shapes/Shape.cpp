#include "shape.h"

int shape::shapeCount;

shape::shape(GfxInfo gfxInfo) : id(shapeCount++), gfxInfo(gfxInfo)
{}

void shape::SetSelected(bool s)
{
	gfxInfo.isSelected = s;
}

bool shape::IsSelected() const
{
	return gfxInfo.isSelected;
}

GfxInfo shape::getGfxInfo() const
{
	return gfxInfo;
}

void shape::setDrawColor(color drawColor)
{
	gfxInfo.DrawClr = drawColor;
}

void shape::setFillColor(color fillColor, bool isFilled = true)
{
	gfxInfo.isFilled = isFilled;
	gfxInfo.FillClr = fillColor;
}

void shape::setGfx(GfxInfo gfxInfo)
{
	this->gfxInfo = gfxInfo;
}

void shape::setID(int ID)
{
	id = ID;
}
