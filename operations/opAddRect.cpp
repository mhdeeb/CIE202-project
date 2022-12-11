#include "opAddRect.h"

#include "../Shapes/Rect.h"

#include <format>

opAddRect::opAddRect(controller* pCont) :operation(pCont)
{}
opAddRect::~opAddRect()
{}

void opAddRect::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point rad;
	int x, y;
	Rect* R = new Rect({}, {}, gfxInfo);
	pUI->PrintMessage("Rectangle Selected: Click on graph to start drawing");
	pUI->GetPointClicked(x, y);
	R->setC1({ x, y });
	pUI->CreateStatusBar(format("({}, {})->", x, y));
	while (!pUI->GetLeftPointState(rad.x, rad.y)) {
		R->setC2(rad);
		pUI->DrawRect(R);
		pControl->getGraph()->Draw(pUI);
		pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", x, y, rad.x, rad.y));
		pUI->CreateDrawToolBar();
		Sleep(16);
		pUI->ClearDrawing();
	}
	pUI->ClearStatusBar();
	pControl->getGraph()->Addshape(R);
}
