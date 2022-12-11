#include "opAddLine.h"

#include "../Shapes/Line.h"

#include <format>

opAddLine::opAddLine(controller* pCont) :operation(pCont)
{}
opAddLine::~opAddLine()
{}

void opAddLine::Execute()
{
	GUI* pUI = pControl->GetUI();
	GfxInfo gfxInfo;
	gfxInfo.DrawClr = pUI->getCrntDrawColor();
	gfxInfo.FillClr = pUI->getCrntFillColor();
	gfxInfo.BorderWdth = pUI->getCrntPenWidth();
	gfxInfo.isFilled = false;
	Point rad;
	int x, y;
	Line* L = new Line({}, {}, gfxInfo);
	pUI->PrintMessage("Line Selected: Click on graph to start drawing");
	pUI->GetPointClicked(x, y);
	L->setPoint1({ x, y });
	pUI->CreateStatusBar(format("({}, {})->", x, y));
	while (!pUI->GetLeftPointState(rad.x, rad.y)) {
		L->setPoint2(rad);
		pUI->DrawLine(L);
		pControl->getGraph()->Draw(pUI);
		pUI->CreateStatusBar(format("Point 1: ({}, {})    Point 2: ({}, {})", x, y, rad.x, rad.y));
		pUI->CreateDrawToolBar();
		Sleep(16);
		pUI->ClearDrawing();
	}
	pUI->ClearStatusBar();
	pControl->getGraph()->Addshape(L);
}
