#include "shape.h"

shape::shape(GfxInfo shapeGfxInfo)
{
	ShpGfxInfo = shapeGfxInfo;	//Default status is non-filled.
}

void shape::SetSelected(bool s)
{
	ShpGfxInfo.isSelected = s;
}

bool shape::IsSelected() const
{
	return ShpGfxInfo.isSelected;
}

GfxInfo shape::getGfxInfo() const
{
	return ShpGfxInfo;
}

void shape::ChngDrawClr(color Dclr)
{
	ShpGfxInfo.DrawClr = Dclr;
}

void shape::ChngFillClr(color Fclr)
{
	ShpGfxInfo.isFilled = true;
	ShpGfxInfo.FillClr = Fclr;
}

